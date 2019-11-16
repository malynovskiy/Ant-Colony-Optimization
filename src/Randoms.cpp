/* Copyright © 2015 Diogo A.B.Fernandes.
** All rights reserved.
**
** Redistribution of this software and use in source and binary forms, with
** or without modification, are permitted without a fee for private, research,
** academic, or other non - commercial purposes, provided that the following
** conditions are met :
**
** *Redistributions of source code must retain the above copyright notice,
** this list of conditionsand the following disclaimer;
** *Redistributions in binary form must reproduce the above copyright notice,
** this list of conditionsand the following disclaimer in the documentation
** and /or other materials provided with the distribution;
** *Neither the name of this software nor the names of its contributors may
** be used to endorse or promote products derived from this software without
** specific prior written permission;
** *Any changes made to this software must be clearly identified as such.
**
** Any use of this software in a commercial environment requires a written
** licence from the copyright owner.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** 	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
** 	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
** 	OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** 	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Randoms.h"
#include <cstdlib>

#include <cmath>
#include <limits>

namespace AntOptimization
{
	double Randoms::Normal(double avg, double sigma)
	{
		return (avg + sigma * gaussdev(&xpto));
	}
	
	double Randoms::Uniforme()
	{
		return ran1(&xpto);
	}
	
	double Randoms::sorte(int m)
	{
		return (1.0 * rand()) / (1.0 * RAND_MAX) * 2.0 * m - m;
	}

	/*
		Taken from Numerical Recipes in C, Chapter 7.
	*/

	float Randoms::ran1(long* idum)
	{
		int j;
		long k;
		static long iy = 0;
		static long iv[NTAB];
		float temp;
		if (*idum <= 0 || !iy) {           // Initialize.
			if (-(*idum) < 1) *idum = 1;     // Be sure to prevent idum = 0.
			else *idum = -(*idum);
			for (j = NTAB + 7; j >= 0; j--) {      // Load the shuffle table (after 8 warm-ups).
				k = (*idum) / IQ;
				*idum = IA * (*idum - k * IQ) - IR * k;
				if (*idum < 0) *idum += IM;
				if (j < NTAB) iv[j] = *idum;
			}
			iy = iv[0];
		}
		k = (*idum) / IQ;                     // Start here when not initializing.
		*idum = IA * (*idum - k * IQ) - IR * k;       // Compute idum=(IA*idum) % IM without over-
		if (*idum < 0) *idum += IM;       // flows by Schrage's method.
		j = iy / NDIV;                        //  Will be in the range 0..NTAB-1.
		iy = iv[j];                         // Output previously stored value and refill the
		iv[j] = *idum;                    // shuffle table.
		if ((temp = AM * iy) > RNMX)
			return RNMX; 				   // Because users don't expect endpoint values.
		else
			return temp;
	}

	float Randoms::gaussdev(long* idum)
	{
		//    float ran1(long *idum);

		static int iset = 0;
		static float gset;
		float fac, rsq, v1, v2;
		if (*idum < 0) iset = 0;      //     Reinitialize.
		if (iset == 0) {            //     We don't have an extra deviate handy, so
			do {
				v1 = 2.0 * ran1(idum) - 1.0;    // pick two uniform numbers in the square ex-
				v2 = 2.0 * ran1(idum) - 1.0;    // tending from -1 to +1 in each direction,
				rsq = v1 * v1 + v2 * v2;          // see if they are in the unit circle,

			} while (rsq >= 1.0 || rsq == 0.0);  // and if they are not, try again.
			fac = sqrt(-2.0 * log(rsq) / rsq);
			// Now make the Box-Muller transformation to get two normal deviates. 
			// Return one and save the other for next time.
			gset = v1 * fac;
			iset = 1;                 //  Set flag.
			return v2 * fac;
		}
		else {                    //   We have an extra deviate handy,
			iset = 0;                 //   so unset the flag,
			return gset;            //   and return it.
		}
	}
}
