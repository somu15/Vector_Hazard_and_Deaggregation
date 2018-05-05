function [AFE_joint, deagg_unif] = Vector_Hazard_and_Deaggregation(Deagg, Deagg_min, Haz_vec, tot_Haz, corr_req)

% Created by Somayajulu Dhulipala on 08/15/2017
% Modified by Somayajulu Dhulipala on 01/31/2018
%
% This function computes vector hazard and vector deaggregation of NIMs 
% using the corresponding scalar M-R deaggregations as inputs. The correlation
% matrix between the NIMs is also required.
%
% THIS CODE IS ONLY APPLICABLE FOR 2 OR 3 IMs IN THE VECTOR SUITE.
% ADDITIONALLY, A GAUSSIAN COPULA IS UTILIZED IN THIS CODE.

% Dhulipala, S.L.N., Rodriguez-Marek,A., and Flint, M.M. "Computation of
% vector hazard using salient features of seismic hazard deaggregation".
% Earthquake Spectra (accepted with minor changes).
%
% NOTATIONS
% NIM = Number of IMs considered in the vector
% NM = Number of magnitude bins in the deaggregation
% NR = Number of distance bins in the deaggregation


% INPUTS:
% -Deagg         NM X NR X NIM    Scalar deaggregations matrix correspoding
% to the hazard levels of NIMs.
% -Deagg_min     NM X NR          Scalar deaggregation matrix for a low IM
% level. To obtain this, select any IM in a PSHA software and perform
% deaggregation for a reasonably low level of the IM.
% -Haz_vec       NIM X 1         Hazard vector containing AFEs for the NIMs
% under consideration.
% -tot_Haz       1 X 1           Total hazard at the site under
% consideration. To obtain this, select any IM in a PSHA software and note
% the ordinate of the hazard curve (in terms of AFE) for a reasonably low 
% level of the IM.
% -corr_req      NIM X NIM       Correlation matrix between the IMs under
% consideration.

% OUTPUTS:
% -AFE_joint     1 X 1           Vector hazard for the IMs under considered
% -deagg_unif    NM X NR         Vector deaggregation for the IMs.


temp = size(Deagg);
NM = temp(1); NR = temp(2); N_IMs = temp(3);

z = zeros(N_IMs,1); prob = zeros(N_IMs,1); deagg_unif = zeros(NM,NR);

for ii = 1:NM
    for jj = 1:NR
        for kk = 1:N_IMs
            joint = Deagg(ii,jj,kk)*Haz_vec(kk);
            joint_min = Deagg_min(ii,jj)*tot_Haz;
            prob(kk) = joint/joint_min;
            z(kk) = norminv(1-prob(kk));
        end
            z = reshape(z, N_IMs,1);
            if N_IMs == 2
                temp2 = mvncdf(z,[0;0],corr_req);
                prob_unif = 1-(1-prob(1))-(1-prob(2))+temp2;
            elseif N_IMs == 3
                temp1 = 1-prob(1); temp2 = 1-prob(2); temp3 = 1-prob(3);
                temp12 = mvncdf([z(1);z(2)],[0;0],[1 corr_req(1,2);corr_req(2,1) 1]);
                temp13 = mvncdf([z(1);z(3)],[0;0],[1 corr_req(1,3);corr_req(3,1) 1]);
                temp23 = mvncdf([z(2);z(3)],[0;0],[1 corr_req(2,3);corr_req(3,2) 1]);
                temp123 = mvncdf(z,[0;0;0],corr_req);
                prob_unif = 1-(temp1+temp2+temp3-temp12-temp13-temp23+temp123);
            else
                break;
            end
            deagg_unif(ii,jj) = prob_unif*joint_min;
    end
end


deagg_unif(isnan(deagg_unif)) = 0;
deagg_unif(isinf(deagg_unif)) = 0;
AFE_joint  = sum(sum(deagg_unif));
deagg_unif = deagg_unif/sum(sum(deagg_unif));
        
       
end
