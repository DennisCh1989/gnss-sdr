#include "recovery_kernel.h"
#include <cmath>
#include <complex>
#include "GPS_L1_CA.h"


unsigned int    recovery_kernel::gen(  float init_phase, float incm_phase,
			               unsigned chunk_length,
			               const lv_32fc_t corr_result,
                                       std::shared_ptr<lv_32fc_t> ref_sig,
			               lv_32fc_t* out,
			               int symb_id)
{
   lv_32fc_t  norm;

   d_symb_ampl += real(corr_result);
   memcpy(&d_in[d_symb_length],ref_sig.get(),sizeof(lv_32fc_t)*chunk_length);
   d_symb_length += chunk_length;
   
   if (symb_id % GPS_CA_TELEMETRY_SYMBOLS_PER_BIT ==  GPS_CA_TELEMETRY_SYMBOLS_PER_BIT-1)
     {
       d_ampl_est+=abs(d_symb_ampl);
       d_ampl_est *= REC_FAC;
      
       lv_32fc_t sign = 1;
       if (d_symb_ampl < 0)
	 sign = -1;
       
        volk_32fc_conjugate_32fc(out, d_in,d_symb_length);
	    
        volk_32fc_x2_conjugate_dot_prod_32fc(&norm, out, out, d_symb_length);
	    
        volk_32fc_s32fc_multiply_32fc(out, out,sign * d_ampl_est*(1-REC_FAC)/ real(norm), d_symb_length);

        lv_32fc_t phase = std::exp(lv_32fc_t(0,init_phase));
	    
        volk_32fc_s32fc_x2_rotator_32fc(out, out, std::exp(lv_32fc_t(0,incm_phase)), &phase, d_symb_length);

	d_symb_ampl =0;
	unsigned int ans = d_symb_length;
	d_symb_length =0;

	return ans;
     }

   return -1;
}

unsigned int  recovery_kernel::clear_rec_ker( lv_32fc_t* out, uint64_t demod_phase)
{
   if (demod_phase % GPS_CA_TELEMETRY_SYMBOLS_PER_BIT !=  GPS_CA_TELEMETRY_SYMBOLS_PER_BIT-1)
     {
        memcpy(out,d_in,sizeof(lv_32fc_t)*d_symb_length);
     }

   unsigned int ans = d_symb_length;

   d_symb_length = 0;

   return ans;	
}








