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
#include "Randoms.h"

namespace AntOptimization
{
	class ACO {
	public:
		ACO(int nAnts, int nCities,
			double alpha, double beta, double q, double ro, double taumax,
			int initCity);
		~ACO();

		void init();

		void connectCITIES(int cityi, int cityj);
		void setCITYPOSITION(int city, double x, double y);

		void printPHEROMONES();
		void printGRAPH();
		void printRESULTS();

		void optimize(int ITERATIONS);

		double getCityCoordinateX(size_t cityNumber);
		double getCityCoordinateY(size_t cityNumber);
	private:
		double distance(int cityi, int cityj);
		bool exists(int cityi, int cityc);
		bool vizited(int antk, int c);
		double PHI(int cityi, int cityj, int antk);

		double length(int antk);

		int city();
		void route(int antk);
		int valid(int antk, int iteration);

		void updatePHEROMONES();

		int NUMBEROFANTS, NUMBEROFCITIES, INITIALCITY;
		double ALPHA, BETA, Q, RO, TAUMAX;

		double BESTLENGTH;
		int* BESTROUTE;

		int** GRAPH, ** ROUTES;
		double** CITIES, ** PHEROMONES, ** DELTAPHEROMONES, ** PROBS;

		Randoms* randoms;
	};
}
