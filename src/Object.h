  #if !defined(Object_h)
  #define Object_h
  class Object{
  public:
  		virtual ~Object();
        virtual bool Equal(Object*);
        virtual void Show();
  };
  #endif

