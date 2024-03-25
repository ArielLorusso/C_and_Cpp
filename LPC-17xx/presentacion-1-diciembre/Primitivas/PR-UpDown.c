#include "PR-UpDown.h"

void InvertirControl(int* num)
{
	int numero = (*num);
	switch(numero)
	{
		case 136:					//invierto adelante detecha con atras dereha
		{   *num = 17;  }break;
		case 17:
		{	*num = 136; }break;

		case 34:					// invierto adelante izquierda con  atras izquierda
		{	*num = 68;  }break;
		case 68:
		{	*num = 34;  }break;

		case 170:					// invierto adelante con atras
		{	*num = 85;  }break;
		case 85:
		{	*num = 170; }break;

		case 153:					// invierto giro derecha con izquierda
		{	*num = 102;	}break;
		case 102:
		{   *num = 153;  }break;
	}
}
