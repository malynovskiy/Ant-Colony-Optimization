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

#pragma once

#define   IA 16807
#define   IM 2147483647
#define   AM (1.0/IM)
#define   IQ 127773
#define   IR 2836
#define   NTAB 32
#define   NDIV (1+(IM-1)/NTAB)
#define   EPS 1.2e-7
#define   RNMX (1.0-EPS)

namespace AntOptimization
{
	class Randoms {

	private:
		long xpto;
	public:
		// Generator seed.
		Randoms(long x) { xpto = -x; }

		// Returns a random Gaussian number.
		double Normal(double avg, double sigma);

		// Returns a uniform random number between 0 and 1.
		double Uniforme();

		// Returns a random number between -m and m.
		double sorte(int m);

		// "Minimal" random number generator of Park and Miller with Bays-Durham shuffle and added
		// safeguards. Returns a uniform random deviate between 0.0 and 1.0 (exclusive of the endpoint values). 
		// Call with idum a negative integer to initialize; thereafter, do not alter idum between successive deviates in a sequence. 
		// RNMX should approximate the largest floating value that is less than 1.
		float ran1(long* idum);

		// Returns a normally distributed deviate with zero mean and unit variance, 
		// using ran1(idum) as the source of uniform deviates.
		float gaussdev(long* idum);
	};
}