#if !defined(INumerable_h)
#define INumerable_h

//Esta clase representa una interfaz para objetos que se 
//pueden numerar, osea establecer un orden.
class INumerable
{
public:
	virtual double GetValue()=0;
};
#endif
