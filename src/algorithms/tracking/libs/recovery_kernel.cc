#include "recovery_kernel.h"
#include <cmath>
#include <complex>
#include "GPS_L1_CA.h"


recovery_kernel rec_ker;

void    recovery_kernel::gen(  float init_phase, float incm_phase,
			       unsigned chunk_length,
			       const lv_32fc_t corr_result,
                               std::shared_ptr<lv_32fc_t> ref_sig,
			       lv_32fc_t* out,
			       int symb_id)
{
   lv_32fc_t  norm;

   if (symb_id <24000)
     d_ampl_est =0;
   else
     {
       d_ampl_est += real(corr_result) *subframe3.get()[symb_id/GPS_CA_TELEMETRY_SYMBOLS_PER_BIT]; 
       d_ampl_est *= REC_FAC;
     }
  
   if (symb_id >= 27500) 
     {
        volk_32fc_conjugate_32fc(out, ref_sig.get(),chunk_length);
	    
        volk_32fc_x2_conjugate_dot_prod_32fc(&norm, out, out, chunk_length);
	    
        volk_32fc_s32fc_multiply_32fc(out, out,subframe3.get()[symb_id/GPS_CA_TELEMETRY_SYMBOLS_PER_BIT] * d_ampl_est*(1-REC_FAC)/ real(norm), chunk_length);

        lv_32fc_t phase = std::exp(lv_32fc_t(0,init_phase));
	    
        volk_32fc_s32fc_x2_rotator_32fc(out, out, std::exp(lv_32fc_t(0,incm_phase)), &phase, chunk_length);
     }
}






