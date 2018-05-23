
#include <volk/volk.h>
#include <memory>
#include <string.h>

const float REC_FAC = 0.96;

class recovery_kernel
{
   public:
     bool gen( float init_phase, float incm_phase,
               unsigned chunk_length,
	       const lv_32fc_t corr_result,
               std::shared_ptr<lv_32fc_t> ref_sig,
	       lv_32fc_t* out,
               int symb_id);
     void put0s(lv_32fc_t* out,int length) {memset(out,0,sizeof(lv_32fc_t) * length);}
     recovery_kernel() {}
     ~recovery_kernel() {} 
     void get_subframe(char * gps_frame);
     void put_sign(float sign) {(sign>0) ? sign_flag = 1 : sign_flag = -1;}
   private:
     float subframe3[2000];
     lv_32fc_t d_ampl_est; 
     float sign_flag;
     int symb_id;
};
