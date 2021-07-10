#include <stdio.h>
#include <stdlib.h>

/*PARA ENCRIPTAR SE DEBE TENER LA IMAGEN EN FORMATO BMP llamada"IMAGEN"*/

int main()
{
	FILE * FP;
  	int CTE=0;
  	int PIXEL;
  	unsigned char R,G,B;

  	printf("\nIniciando programa...\n");

	if((FP = fopen("IMAGEN.bmp","r+b"))==NULL)
	{
		printf("\nERROR APERTURA DE ARCHIVO BMP.\n");
		exit(1);
	};

	/*LLEVO LA VENTANA AL INICIO DE LA IMAGEN*/
	fseek(FP,(long)(54*sizeof(char)),SEEK_SET);

	printf("\nModificando cada pixel...\n");
	/*A CADA PIXEL LE HAGO EL COMPLEMENTO A 1 Y LUEGO RESTO UNA CTE 2547*/
	fread(&PIXEL ,(3*sizeof(char)),1,FP);
	while(!feof(FP))
	{
		PIXEL=PIXEL-CTE;
		PIXEL=(~PIXEL);
		fseek(FP,(long)(-3*sizeof(char)),SEEK_CUR);
		fwrite(&PIXEL ,(3*sizeof(char)),1,FP);

		fseek(FP,0,SEEK_CUR);
		fread(&PIXEL ,(3*sizeof(char)),1,FP);

		CTE=2547-CTE;
	};

	printf("\nModificacion de pixel terminado.\n\n\n");

								/*CAMBIO DE COLORES MODIFICADOS*/

	/*LLEVO LA VENTANA AL INICIO DE LA IMAGEN*/
	fseek(FP,(long)(54*sizeof(char)),SEEK_SET);

	printf("\nCambio de colores modificados...\n");

	while(!feof(FP))
	{
		fread(&B ,(1*sizeof(char)),1,FP);
		fread(&G ,(1*sizeof(char)),1,FP);
		fread(&R ,(1*sizeof(char)),1,FP);

		if(B>200 && G<105 && R<100)	/*IDENTIFICO COLOR AZUL*/
		{
			fseek(FP,(long)(-3*sizeof(char)),SEEK_CUR);	/*REGRESO A LA POSICION DEL COLOR MODIFICADO*/
			B=~B;
			fwrite(&B ,(1*sizeof(char)),1,FP);
			fwrite(&G ,(1*sizeof(char)),1,FP);
			fwrite(&R ,(1*sizeof(char)),1,FP);
			fseek(FP,0,SEEK_CUR);
		};

		if(B>130 && G<50 && R>130)	/*IDENTIFICO COLOR ROSA*/
		{
			fseek(FP,(long)(-3*sizeof(char)),SEEK_CUR);	/*REGRESO A LA POSICION DEL COLOR MODIFICADO*/
			G=~G;
			fwrite(&B ,(1*sizeof(char)),1,FP);
			fwrite(&G ,(1*sizeof(char)),1,FP);
			fwrite(&R ,(1*sizeof(char)),1,FP);
			fseek(FP,0,SEEK_CUR);
		};

		if(B<100 && G<80 && R>107)	/*IDENTIFICO COLOR ROJO*/
		{
			fseek(FP,(long)(-3*sizeof(char)),SEEK_CUR);	/*REGRESO A LA POSICION DEL COLOR MODIFICADO*/
			R=~R;
			B=~B;
			G=~G;
			fwrite(&B ,(1*sizeof(char)),1,FP);
			fwrite(&G ,(1*sizeof(char)),1,FP);
			fwrite(&R ,(1*sizeof(char)),1,FP);
			fseek(FP,0,SEEK_CUR);
		};

		if(B<100 && G>200 && R<117)	/*IDENTIFICO COLOR VERDE*/
		{
			fseek(FP,(long)(-3*sizeof(char)),SEEK_CUR);	/*REGRESO A LA POSICION DEL COLOR MODIFICADO*/
			B=~B;
			fwrite(&B ,(1*sizeof(char)),1,FP);
			fwrite(&G ,(1*sizeof(char)),1,FP);
			fwrite(&R ,(1*sizeof(char)),1,FP);
			fseek(FP,0,SEEK_CUR);
		};
	};

	fclose(FP);

	printf("\nFin del programa.\n");
	return 0;
};
