#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

double u,v,w;
double z;
double a,b;
double d,q;
double iu,iv,iw;
double ia,ib;
double t;
double k1=sqrt(3.0);
double k2=1.0/sqrt(3.0);
double ampl=17.147;

void clarke ()
{
	a=u;
	//b=k2*(u+2*v);		//metodo alternativo senza usare w
	b=k2*(v-w);
}

void park ()
{
	double sin_t=sin((t/360.0)*2*M_PI);
	double cos_t=cos((t/360.0)*2*M_PI);

	d=a*cos_t-b*sin_t;
	q=b*cos_t+a*sin_t;
}

void inv_clarke ()
{
	iu=a;
	iv=(-a+k1*b)/2;
	iw=(-a-k1*b)/2;
}

void inv_park ()
{
	double sin_t=sin((t/360.0)*2*M_PI);
	double cos_t=cos((t/360.0)*2*M_PI);

	ia=d*cos_t+q*sin_t;
	ib=q*cos_t-d*sin_t;
}

void module ()
{
	z=sqrt(u*u+v*v+w*w);
}

int main ()
{
	FILE *fp;

	fp=fopen("Clarke_Park.txt","w");

	printf("Clarke Park direct and inverse\n");
	fprintf(fp,"Clarke Park direct and inverse\n");

	for (t=0;t<360;t+=10)
	{
		u=sin(((t+0.0)/(360.0))*2*M_PI)*ampl;
		v=sin(((t+120.0)/(360.0))*2*M_PI)*ampl;
		w=sin(((t+240.0)/(360.0))*2*M_PI)*ampl;
		clarke();
		park();
		inv_clarke();
		inv_park();
		module();
		printf("angle = %03d => %1.4f %1.4f %1.4f\n",(int)(t),(t/360.0)*2*M_PI,z,z/q);
		printf("Direct  => u=%1.4f v=%1.4f w=%1.4f a=%1.4f b=%1.4f d=%1.4f q=%1.4f\n",u,v,w,a,b,d,q);
		printf("Inverse => u=%1.4f v=%1.4f w=%1.4f a=%1.4f b=%1.4f d=%1.4f q=%1.4f\n",iu,iv,iw,ia,ib,d,q);
		fprintf(fp,"angle = %03d => %1.4f %1.4f\n",(int)(t),(t/360.0)*2*M_PI,z/q);
		fprintf(fp,"Direct  => u=%1.4f v=%1.4f w=%1.4f a=%1.4f b=%1.4f d=%1.4f q=%1.4f\n",u,v,w,a,b,d,q);
		fprintf(fp,"Inverse => u=%1.4f v=%1.4f w=%1.4f a=%1.4f b=%1.4f d=%1.4f q=%1.4f\n",iu,iv,iw,ia,ib,d,q);
	}
	fclose(fp);
}
