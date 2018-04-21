#ifndef REFERENCE_MAP_H
#define REFERENCE_MAP_H

#include <src/image.h>
#include <src/projector.h>
#include <vector>

class ObservationModel;

class ReferenceMap
{
    public:

        typedef enum {Own, Opposite} HalfSet;

        ReferenceMap();
	
			// input parameters:
            std::string reconFn0, reconFn1, maskFn, fscFn;
            double paddingFactor, kmin;

            // data:
            Image<RFLOAT> freqWeight;
            std::vector<double> freqWeight1D;
            Projector projectors[2];
            int k_out, s, sh;

        void read(IOParser& parser, int argc, char *argv[]);
        void load(int verb, bool debug);
		
		Image<RFLOAT> getHollowWeight(double kmin_px);

        std::vector<Image<Complex>> predictAll(
                const MetaDataTable& mdt,
                const ObservationModel& obs,
                HalfSet hs, int threads,
                bool applyCtf = true,
                bool applyTilt = true);

        Image<Complex> predict(
                const MetaDataTable& mdt, int p,
                const ObservationModel& obs,
                HalfSet hs,
                bool applyCtf = true,
                bool applyTilt = true);

};

#endif
