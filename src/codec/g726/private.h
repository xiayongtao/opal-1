/**
 *
 * $Log: private.h,v $
 * Revision 1.1  2002/02/11 23:24:23  robertj
 * Updated to openH323 v1.8.0
 *
 * Revision 1.2  2002/02/10 21:14:54  dereks
 * Add cvs log history to head of the file.
 * Ensure file is terminated by a newline.
 *
 *
 *
 */
#ifdef G726_PRIVATE
#define G726_PRIVATE

unsigned char linear2ulaw(int pcm_val);
int ulaw2linear(unsigned char u_val);
unsigned char linear2alaw(int pcm_val);
int alaw2linear(unsigned char u_val);
static int fmult(	int		an,	int		srn);
int predictor_zero(	g726_state *state_ptr);
int predictor_pole(	g726_state *state_ptr);
int step_size(	g726_state *state_ptr);
int quantize(	int		d,	/* Raw difference signal sample */
	int		y,	/* Step size multiplier */
	short		*table,	/* quantization table */
	int		size);	/* table size of short integers */
int reconstruct(	int		sign,	/* 0 for non-negative value */
	int		dqln,	/* G.72x codeword */
	int		y);	/* Step size multiplier */
void update(	int		code_size,	/* distinguish 723_40 with others */
	int		y,		/* quantizer step size */
	int		wi,		/* scale factor multiplier */
	int		fi,		/* for long/short term energies */
	int		dq,		/* quantized prediction difference */
	int		sr,		/* reconstructed signal */
	int		dqsez,		/* difference from 2-pole predictor */
	g726_state *state_ptr);	/* coder state pointer */
int tandem_adjust_alaw(
	int		sr,	/* decoder output linear PCM sample */
	int		se,	/* predictor estimate sample */
	int		y,	/* quantizer step size */
	int		i,	/* decoder input code */
	int		sign,
	short		*qtab);
int tandem_adjust_ulaw(
	int		sr,	/* decoder output linear PCM sample */
	int		se,	/* predictor estimate sample */
	int		y,	/* quantizer step size */
	int		i,	/* decoder input code */
	int		sign,
	short		*qtab);

#endif // G726_PRIVATE

