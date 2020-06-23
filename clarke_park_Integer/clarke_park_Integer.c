#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdint.h>

#define M_PI 3.14159265358979323846

int32_t u,v,w;
int32_t a,b;
int32_t d,q;
int32_t iu,iv,iw;
int32_t ia,ib;
int16_t t;
int16_t sin_t;
int16_t cos_t;
int32_t k1=(int32_t)(sqrt(3.0)*32768.0);
int32_t k2=(int32_t)(1.0/sqrt(3.0)*32768.0);
int16_t ampl=800;
int16_t sin_tab[90+1];

double z;

void gen_sin_tab()
{
	int16_t i;

	for (i=0;i<=90;i++)
	{
		sin_tab[i]=sin(((double)(i)/(90.0))*M_PI/2)*32767;
	}
}

int16_t sine(int16_t angle)
{
	angle=angle%360;
	if (angle<=180)
		if (angle<=90)
			return sin_tab[angle];
		else
			return sin_tab[180-angle];
	return -sine(360-angle);
}

int16_t cosine(int16_t angle)
{
	return sine(angle+90);
}

void clarke ()
{
	a=u;
	//b=k2*(u+2*v)/32768;		//metodo alternativo senza usare w
	b=k2*(v-w)/32768;
}

void park ()
{
	d=(a*cos_t-b*sin_t)/32768;
	q=(b*cos_t+a*sin_t)/32768;
}

void inv_clarke ()
{
	iu=a;
	iv=(-a+((k1*b)/32768))/2;
	iw=(-a-((k1*b)/32768))/2;
}

void inv_park ()
{
	ia=(d*cos_t+q*sin_t)/32768;
	ib=(q*cos_t-d*sin_t)/32768;
}

void module ()
{
	z=sqrt(u*u+v*v+w*w);
}

int main ()
{
	FILE *fp;

	fp=fopen("Clarke_Park.txt","w");

	gen_sin_tab();

	printf("Clarke Park direct and inverse 32bit integer\n");
	fprintf(fp,"Clarke Park direct and inverse 32bit integer\n");

	for (t=0;t<360;t+=10)
	{
		u=(sine(t+0)*ampl)/32768;
		v=(sine(t+120)*ampl)/32768;
		w=(sine(t+240)*ampl)/32768;
		sin_t=sine(t+0);
		cos_t=cosine(t+0);
		clarke();
		park();
		inv_clarke();
		inv_park();
		module();
		printf("angle = %03d %1.4f\n",(int)(t),z/q);
		printf("Direct  => u=%d v=%d w=%d a=%d b=%d d=%d q=%d\n",u,v,w,a,b,d,q);
		printf("Inverse => u=%d v=%d w=%d a=%d b=%d d=%d q=%d\n",iu,iv,iw,ia,ib,d,q);
		fprintf(fp,"angle = %d %1.4f\n",(int)(t),(t/360.0)*2*M_PI,z/q);
		fprintf(fp,"Direct  => u=%d v=%d w=%d a=%d b=%d d=%d q=d\n",u,v,w,a,b,d,q);
		fprintf(fp,"Inverse => u=%d v=%d w=%d a=%d b=%d d=%d q=%d\n",iu,iv,iw,ia,ib,d,q);
	}
	fclose(fp);
}
