# Vector_Hazard_and_Deaggregation

This function computes vector hazard and vector deaggregation of NIMs 
using the corresponding scalar M-R deaggregations as inputs. The correlation
matrix between the NIMs is also required. Refer to the Example_Inputs.mat
file for example inputs.

Dhulipala, S.L.N., Rodriguez-Marek, A., and Flint, M.M. "Computation of
vector hazard using salient features of seismic hazard deaggregation".
Earthquake Spectra (accepted).

NOTATIONS
NIM = Number of IMs considered in the vector.
NM = Number of magnitude bins in the deaggregation.
NR = Number of distance bins in the deaggregation.


INPUTS:
-Deagg         (NM X NR X NIM)    Scalar deaggregations matrix corresponding
to the hazard levels of NIMs.
-Deagg_min     (NM X NR)          Scalar deaggregation matrix for a low IM
level. To obtain this, select any IM in a PSHA software and perform
deaggregation for a reasonably low IM level.
-Haz_vec       (NIM X 1)         Hazard vector containing AFEs for the NIMs
under consideration.
-tot_Haz       (1 X 1)           Total hazard at the site under
consideration. To obtain this, select any IM in a PSHA software and note
the ordinate of the hazard curve (in terms of AFE) for a reasonably low IM 
level.
-corr_req      (NIM X NIM)       Correlation matrix between the IMs under
consideration.

OUTPUTS:
-AFE_joint     (1 X 1)           Vector hazard for the IMs under consideration.
-deagg_unif    (NM X NR)         Vector deaggregation for the IMs.
