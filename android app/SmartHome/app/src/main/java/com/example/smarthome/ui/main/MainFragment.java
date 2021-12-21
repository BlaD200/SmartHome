package com.example.smarthome.ui.main;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;
import androidx.core.os.HandlerCompat;
import androidx.databinding.DataBindingUtil;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.MutableLiveData;

import com.example.smarthome.R;
import com.example.smarthome.databinding.MainFragmentBinding;
import com.example.smarthome.ui.main.request.RequestExecutor;
import com.example.smarthome.ui.main.request.Result;
import com.neovisionaries.ws.client.HostnameUnverifiedException;
import com.neovisionaries.ws.client.OpeningHandshakeException;
import com.neovisionaries.ws.client.WebSocket;
import com.neovisionaries.ws.client.WebSocketAdapter;
import com.neovisionaries.ws.client.WebSocketException;
import com.neovisionaries.ws.client.WebSocketFactory;

import java.io.IOException;
import java.text.DecimalFormat;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.regex.Pattern;

public class MainFragment extends Fragment {

    private MainFragmentBinding mBinding;
    private final MutableLiveData<Float> mTemperature = new MutableLiveData<>();
    private final MutableLiveData<Float> mHumidity = new MutableLiveData<>();

    private Handler mMainThreadHandler;
    private RequestExecutor mRequestExecutor;
    private WebSocket mWebSocket;

    private static final String TAG = MainFragment.class.getCanonicalName();
    private static final String WEB_SOCKET_IP = "192.168.0.188";
    private static final String CHANNEL_ID = "CHANNEL_ALERT";
    private static int NOTIFICATION_ID = 0;

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container,
                             Bundle savedInstanceState) {
        mBinding = DataBindingUtil.inflate(inflater,
                R.layout.main_fragment, container, false);
        mBinding.setLifecycleOwner(this);
        mBinding.setTemperature(mTemperature);
        mBinding.setHumidity(mHumidity);
        return mBinding.getRoot();
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        mBinding.btnAlert.setOnClickListener(v -> {
            mWebSocket.sendText("alert");
        });

        mTemperature.setValue(-1.0f);
        mHumidity.setValue(-1.0f);

        ExecutorService executor = Executors.newFixedThreadPool(5);
        mMainThreadHandler = HandlerCompat.createAsync(Looper.getMainLooper());
        mRequestExecutor = new RequestExecutor(executor, mMainThreadHandler);

        createNotificationChannel();

        try {
            mWebSocket = new WebSocketFactory().createSocket("ws://" + WEB_SOCKET_IP + "/ws");
        } catch (IOException e) {
            Log.e(TAG, "Failed to create web socket");
            return;
        }

        mWebSocket.addListener(new WebSocketAdapter() {
            @Override
            public void onTextMessage(WebSocket websocket, String message) {
                if (message.equals("alert")) {
                    showAlertNotification();
                } else if (message.startsWith("data")) {
                    String data = message.substring(4);
                    String[] temperatureAndHumidity = data.split("\\|");
                    if (temperatureAndHumidity.length == 2) {
                        try {
                            float temperature = Float.parseFloat(temperatureAndHumidity[0]);
                            float humidity = Float.parseFloat(temperatureAndHumidity[1]);
                            mMainThreadHandler.post(() -> {
                                mTemperature.setValue(round(temperature));
                                mHumidity.setValue(round(humidity));
                            });
                        } catch (NumberFormatException ignored) {
                        }
                    }
                }
            }
        });

        mRequestExecutor.execute(() -> {
            try {
                try {
                    // Connect to the server and perform an opening handshake.
                    // This method blocks until the opening handshake is finished.
                    mWebSocket.connect();
                } catch (OpeningHandshakeException e) {
                    Log.e(TAG, "A violation against the WebSocket protocol " +
                            "was detected during the opening handshake");
                    throw e;
                } catch (HostnameUnverifiedException e) {
                    Log.e(TAG, "The certificate of the peer does not match the expected hostname");
                    throw e;
                } catch (WebSocketException e) {
                    Log.e(TAG, "Failed to establish a WebSocket connection");
                    throw e;
                }
                return new Result.Success<>(true);
            } catch (WebSocketException e) {
                return new Result.Error(e);
            }
        }, (result) -> {
            if (result instanceof Result.Success) {
                mBinding.btnAlert.setEnabled(true);
                Log.i(TAG, "WebSocket initiated successfully");
            } else if (result instanceof Result.Error) {
                Exception exc = ((Result.Error) result).exception;
                mBinding.labelError.setText(exc.getLocalizedMessage());
                mBinding.labelError.setVisibility(View.VISIBLE);
                Log.e(TAG, "WebSocket setup failed. " + exc.getMessage());
            }
        });
    }

    private void createNotificationChannel() {
        // Create the NotificationChannel, but only on API 26+ because
        // the NotificationChannel class is new and not in the support library
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            CharSequence name = getString(R.string.channel_name);
            String description = getString(R.string.channel_description);
            int importance = NotificationManager.IMPORTANCE_HIGH;
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, name, importance);
            channel.setDescription(description);
            // Register the channel with the system; you can't change the importance
            // or other notification behaviors after this
            NotificationManager notificationManager = requireContext()
                    .getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }
    }

    private void showAlertNotification() {
        NotificationCompat.Builder builder = new NotificationCompat
                .Builder(requireContext(), CHANNEL_ID)
                .setSmallIcon(R.drawable.ic_launcher_background)
                .setContentTitle("Alert | Smart Home")
                .setContentText("Attention! Alert has been triggered")
                .setPriority(NotificationCompat.PRIORITY_MAX);

        NotificationManagerCompat notificationManager = NotificationManagerCompat
                .from(requireContext());
        notificationManager.notify(NOTIFICATION_ID++, builder.build());
    }

    private float round(float num) {
        return (float) Math.round(num * 10) / 10;
    }
}