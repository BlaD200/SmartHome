#ifndef BASE_VIEW
#define BASE_VIEW

template <typename T>
class BaseView
{
protected:
    const T& _model;

    virtual void _updateView() = 0;

public:
    BaseView(const T& model): _model(model) {};
    ~BaseView(){};
    
    virtual void updateView() final {
        _updateView();
    }
};


#endif // BASE_VIEW
