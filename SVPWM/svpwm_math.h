#ifndef SVPWM_MATH_H
#define SVPWM_MATH_H
#include <stdint.h>

#if Q_HEX
#define Q15 		(int16_t)0x8000
#define Q14			(int16_t)0x4000
#define Q13			(int16_t)0x2000
#define Q12			(int16_t)0x1000
#define Q11			(int16_t)0x0800
#define Q10			(int16_t)0x0400
#define Q9			(int16_t)0x0200
#define	Q8			(int16_t)0x0100
#define	Q7			(int16_t)0x0080
#define	Q6			(int16_t)0x0040
#define	Q5			(int16_t)0x0020
#define	Q4			(int16_t)0x0010
#define	Q3			(int16_t)0x0008
#define	Q2			(int16_t)0x0004
#define	Q1			(int16_t)0x0002
#define	Q0			(int16_t)0x0001
#else
#define Q15 		(int16_t)32768
#define Q14			(int16_t)16384
#define Q13			(int16_t)8192
#define Q12			(int16_t)4096
#define Q11			(int16_t)2048
#define Q10			(int16_t)1024
#define Q9			(int16_t)512
#define	Q8			(int16_t)256
#define	Q7			(int16_t)128
#define	Q6			(int16_t)64
#define	Q5			(int16_t)32
#define	Q4			(int16_t)16
#define	Q3			(int16_t)8
#define	Q2			(int16_t)4
#define	Q1			(int16_t)2
#define	Q0			(int16_t)1
#endif



#define MAX_INT16	(int16_t)32768
#define MIN_INT16	(int16_t)-32768

#define MAX_INT32	(int32_t)2147483647
#define MIN_INT32	(int32_t)-2147483648

#define SINE_TABLE_SIZE		360
extern const int32_t sine_table[SINE_TABLE_SIZE];
extern const int32_t consine_table[SINE_TABLE_SIZE];
extern const int16_t sine_table_8192[SINE_TABLE_SIZE];
extern const int16_t consine_table_8192[SINE_TABLE_SIZE];

/**
  * @brief Two components stator current type definition
  */
typedef struct
{
  int16_t qI_Component1;
  int16_t qI_Component2;
} Curr_Components;

/**
  * @brief  Two components stator voltage type definition
  */
typedef struct
{
  int16_t qV_Component1;
  int16_t qV_Component2;
} Volt_Components;

/**
  * @brief  Trigonometrical functions type definition
  */
typedef struct
{
  int16_t hCos;
  int16_t hSin;
} Trig_Components;


/**
  * @brief  This function transforms stator currents Ia and qIb (which are
  *         directed along axes each displaced by 120 degrees) into currents
  *         Ialpha and Ibeta in a stationary qd reference frame.
  *                               Ialpha = Ia
  *                       Ibeta = -(2*Ib+Ia)/sqrt(3)
  * @param  Curr_Input: stator current Ia and Ib in Curr_Components format
  * @retval Stator current Ialpha and Ibeta in Curr_Components format
  */
Curr_Components clarke( Curr_Components Curr_Input );

/**
  * @brief  This function transforms stator currents Ialpha and Ibeta, which
  *         belong to a stationary qd reference frame, to a rotor flux
  *         synchronous reference frame (properly oriented), so as Iq and Id.
  *                   Id= Ialpha *sin(theta)+qIbeta *cos(Theta)
  *                   Iq=qIalpha *cos(Theta)-qIbeta *sin(Theta)
  * @param  Curr_Input: stator current Ialpha and Ibeta in Curr_Components format
  * @param  Theta: rotating frame angular position in q1.15 format
  * @retval Stator current Iq and Id in Curr_Components format
  */
Curr_Components park( Curr_Components Curr_Input, int16_t Theta );

/**
  * @brief  This function transforms stator voltage qVq and qVd, that belong to
  *         a rotor flux synchronous rotating frame, to a stationary reference
  *         frame, so as to obtain qValpha and qVbeta:
  *                  Valfa= Vq*Cos(theta)+ Vd*Sin(theta)
  *                  Vbeta=-Vq*Sin(theta)+ Vd*Cos(theta)
  * @param  Curr_Input: stator voltage Vq and Vd in Volt_Components format
  * @param  Theta: rotating frame angular position in q1.15 format
  * @retval Stator voltage Valpha and Vbeta in Volt_Components format
  */
Volt_Components rev_park( Volt_Components Volt_Input, int16_t Theta );


/**
  * @brief  This function returns cosine and sine functions of the angle fed in
  *         input
  * @param  hAngle: angle in q1.15 format
  * @retval Trig_Components Cos(angle) and Sin(angle) in Trig_Components format
  */
Trig_Components trig_functions( int16_t hAngle );



#endif
