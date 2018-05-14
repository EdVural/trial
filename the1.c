

#include <stdio.h>
#include <math.h>
double f(double x);

int main()
{
	double interval_lower, interval_upper, tolerance;
	double x1, x2, epsilon, f_der;
	epsilon = 0.0001;
	scanf("%lf %lf %lf", &interval_lower, &interval_upper, &tolerance);
	x1 = interval_lower + 0.1;

	while ((x1 < interval_upper) && (x1>interval_lower))
	{


		f_der = (f(x1 + epsilon) - f(x1 - epsilon)) / (2 * epsilon);
		if ((f_der < 0.01) && (f_der > -0.01))
		{
			x1 += 0.5;
			continue;

		}



		x2 = x1 - f(x1) / f_der;


		if (x2 <interval_lower)
		{
			x1 += 1.0;
			continue;
		}




		

		if ((f(x2)  < 0.0001) && (f(x2)  > -0.0001))
		{
			printf("%f ", x2);

			x2 += 0.1;
			while (x2<interval_upper) {
				f_der = (f(x2 + epsilon) - f(x2 - epsilon)) / (2 * epsilon);
				if ((f_der < 0.1) && (f_der > -0.1))
				{

					break;
				}
				else {
					x2 += 0.01;
				}


			}
			x1 = x2 + 0.1;




		}
		else {
			x1 = x2;
		}
	}
	return 0;
}
