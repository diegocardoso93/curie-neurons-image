/******************************************************************************/
/*	CurieNeurons.h	--	Driver for the Curie module  			    
 *  revision 1.0, April 22, 2016 
 *	Copyright (c) 2016, General Vision Inc, All rights reserved	
 *
 * http://general-vision.com/documentation/TM_NeuroMem_Technology_Reference_Guide.pdf
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/******************************************************************************/

/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include "CurieNeurons.h"

using namespace std;
extern "C" {
  #include <stdint.h>
}

/* PVP */
#define PVP_REGISTER_BASE   (0xB0600000)
#define NM_NCR       		*(volatile int*)(PVP_REGISTER_BASE + 0x00)
#define NM_COMP             *(volatile int*)(PVP_REGISTER_BASE + 0x04)
#define NM_LCOMP            *(volatile int*)(PVP_REGISTER_BASE + 0x08)
#define NM_DIST         	*(volatile int*)(PVP_REGISTER_BASE + 0x0C)
#define NM_IDX        		*(volatile int*)(PVP_REGISTER_BASE + 0x0C)
#define NM_CAT              *(volatile int*)(PVP_REGISTER_BASE + 0x10)
#define NM_AIF              *(volatile int*)(PVP_REGISTER_BASE + 0x14)
#define NM_MINIF            *(volatile int*)(PVP_REGISTER_BASE + 0x18)
#define NM_MAXIF            *(volatile int*)(PVP_REGISTER_BASE + 0x1C)
#define NM_TESTCOMP         *(volatile int*)(PVP_REGISTER_BASE + 0x20)
#define NM_TESTCAT          *(volatile int*)(PVP_REGISTER_BASE + 0x24)
#define NM_NID              *(volatile int*)(PVP_REGISTER_BASE + 0x28)
#define NM_GCR        		*(volatile int*)(PVP_REGISTER_BASE + 0x2C)
#define NM_RSTCHAIN       	*(volatile int*)(PVP_REGISTER_BASE + 0x30)
#define NM_NSR              *(volatile int*)(PVP_REGISTER_BASE + 0x34)
#define NM_FORGET  			*(volatile int*)(PVP_REGISTER_BASE + 0x3C)
#define NM_NCOUNT    		*(volatile int*)(PVP_REGISTER_BASE + 0x3C)

// ------------------------------------------------------------ //
//    Constructor to the class CurieNeurons
// ------------------------------------------------------------ 
CurieNeurons::CurieNeurons(){	
}
// --------------------------------------------------------------
//  Initialize the neural network clearing any previous knowledge.
// --------------------------------------------------------------
int CurieNeurons::begin()
{
	NM_FORGET=0;
	if (NM_MINIF==2) return(0); else return(1);
}
// ------------------------------------------------------------ 
// Report the neural network status and capacity
// ------------------------------------------------------------ 
void CurieNeurons::getNeuronsInfo(int* neuronSize, int* neuronsAvailable, int* neuronsCommitted)
{
	*neuronSize=NEURONSIZE;
	*neuronsAvailable=MAXNEURONS;
	*neuronsCommitted=NM_NCOUNT;
}
// ------------------------------------------------------------ 
// Un-commit all the neurons, so they become ready to learn
// Reset the Maximum Influence Field to default value=0x4000
// ------------------------------------------------------------ 
void CurieNeurons::forget()
{
	NM_FORGET=0;
}
// ------------------------------------------------------------ 
// Un-commit all the neurons, so they become ready to learn,
// Set the Maximum Influence Field (default value=0x4000)
// ------------------------------------------------------------ 
void CurieNeurons::forget(int Maxif)
{
	NM_FORGET=0;
	NM_MAXIF=Maxif;
}
//-----------------------------------------------
// Learn a vector as belonging to category
// and return the number of committed neurons
//----------------------------------------------
int CurieNeurons::learn(unsigned char vector[], int length, int category)
{
	if (length> NEURONSIZE) length=NEURONSIZE;
	for (int i=0; i<length-1; i++) NM_COMP=vector[i];
	NM_LCOMP=vector[length-1];
	NM_CAT=category;
	return(NM_NCOUNT);
}
//----------------------------------------------
// Recognize a vector and return the best match, or the 
// category, distance and identifier of the top firing neuron
//----------------------------------------------
int CurieNeurons::classify(unsigned char vector[], int length, int* distance, int* category, int* nid)
{
	if (length> NEURONSIZE) length=NEURONSIZE;
	for (int i=0; i<length-1; i++) NM_COMP=vector[i];
	NM_LCOMP=vector[length-1];
	*distance = NM_DIST;
	*category= NM_CAT & 0x7FFF; //Degenerated bit15 is masked
	*nid =NM_NID;
	return(NM_NSR);
}
//----------------------------------------------
// Recognize a vector and return the response  of up to K top firing neurons
// The response includes the distance, category and identifier of the neuron
// The Degenerated flag of the category is masked
// Return the number of firing neurons or K whichever is smaller
//----------------------------------------------
int CurieNeurons::classify(unsigned char vector[], int length, int K, int distance[], int category[], int nid[])
{
	int responseNbr=0;
	if (length> NEURONSIZE) length=NEURONSIZE;
	for (int i=0; i<length-1; i++) NM_COMP=vector[i];
	NM_LCOMP=vector[length-1];
	for (int i=0; i<K; i++)
	{
		distance[i] = NM_DIST;
		if (distance[i]==0xFFFF)
		{ 
			category[i]=0xFFFF;
			nid[i]=0xFFFF;
		}
		else
		{
			responseNbr++;
			category[i]= NM_CAT & 0x7FFF; //Degenerated bit15 is masked
			nid[i] = NM_NID;
		}
	}
return(responseNbr);
}
//-------------------------------------------------------------
// Read the contents of the neuron pointed by index in the chain of neurons
// starting index is 1
//-------------------------------------------------------------
void CurieNeurons::readNeuron(int nid, int* context, unsigned char model[], int* aif, int* category)
{
	if (nid==0) return;
	int TempNSR=NM_NSR;
	NM_NSR=0x0010;
	NM_RSTCHAIN= 0;
	for (int i=0; i< nid-1; i++) NM_CAT; // move to index in the chain of neurons
	*context=NM_NCR;
	for (int j=0; j<NEURONSIZE; j++) model[j]=NM_COMP;
	*aif=NM_AIF;
	*category=NM_CAT;
	NM_NSR=TempNSR; // set the NN back to its calling status
}
//----------------------------------------------------------------------------
// Read the contents of the committed neurons
// The neurons array should be sized to HEADERSIZE + MAXNEURON * (NEURONSIZE + 8)
// Default header size of 8 bytes: headerSize, reserved, 2-bytes MaxLength, 4-bytes neuronCount
// followed by neuroCount record of (MaxLength + 8) bytes: 
// 2-bytes NCR, MaxLength-bytes COMP, 2-bytes AIF, 2-bytes MINIF, 2-bytes CAT
//----------------------------------------------------------------------------
int CurieNeurons::readNeurons(unsigned char neurons[])
{
	int ncount= NM_NCOUNT;
	int TempNSR= NM_NSR; // save value to restore NN status upon exit of the function
	NM_NSR= 0x0010;
	NM_RSTCHAIN= 0;
	int offset=8;
	int MaxLength=NEURONSIZE; //can be less than NEURONSIZE
	int recLen=MaxLength+8; // memory plus 8 bytes of register data
	neurons[0]= offset; // default header size of 8 bytes
	neurons[1]= 0; // reserved to encode a future format identifier
	neurons[2]= (MaxLength & 0xFF00)>>8;
	neurons[3]= (MaxLength & 0x00FF);
	neurons[4]= (ncount & 0xFF000000)>>24;
	neurons[5]= (ncount & 0x00FF0000)>>16;
	neurons[6]= (ncount & 0x0000FF00)>>8;
	neurons[7]= (ncount & 0x000000FF);
	int Temp;	
	for (int i=0; i< ncount; i++)
	{
		offset+=(i*recLen);
		Temp=NM_NCR;
		neurons[ offset]=(unsigned char)((Temp & 0xFF00)>>8);
		neurons[ offset + 1]=(unsigned char)(Temp & 0x00FF);
		for (int j=0; j< MaxLength; j++) 
		{
			Temp=NM_COMP;
			neurons[ offset + 2 + j]=(unsigned char)(Temp & 0x00FF);
		}
		Temp=NM_AIF;
		neurons[ offset + MaxLength + 2]=(unsigned char)((Temp & 0xFF00)>>8);
		neurons[ offset + MaxLength + 3]=(unsigned char)(Temp & 0x00FF);
		Temp=NM_MINIF;
		neurons[ offset + MaxLength + 4]=(unsigned char)((Temp & 0xFF00)>>8);
		neurons[ offset + MaxLength + 5]=(unsigned char)(Temp & 0x00FF);
		Temp=NM_CAT;
		neurons[ offset + MaxLength + 6]=(unsigned char)((Temp & 0xFF00)>>8);
		neurons[ offset + MaxLength + 7]=(unsigned char)(Temp & 0x00FF);
	}
	NM_NSR=TempNSR; // set the NN back to its calling status
	return(ncount);
}
//---------------------------------------------------------------------
// Clear the committed neurons and restore a new content for the neurons
// from an input array formatted as follows
// Default header size of 8 bytes: headerSize, reserved, 2-bytes MaxLength, 4-bytes neuronCount
// followed by neuroCount record of (MaxLength + 8) bytes: 
// 2-bytes NCR, MaxLength-bytes COMP, 2-bytes AIF, 2-bytes MINIF, 2-bytes CAT
//---------------------------------------------------------------------
int CurieNeurons::writeNeurons(unsigned char neurons[])
{
	int offset= neurons[0];
	int MaxLength= (neurons[2]*256) + neurons[3];
	int ncount= (neurons[4]<<24) + (neurons[5]<<16) + (neurons[6]<<8) + neurons[7];
	if (ncount>MAXNEURONS) ncount=MAXNEURONS;
	int recLen=MaxLength+8;	
	int TempNSR=NM_NSR; // save value to restore NN status upon exit of the function
	int TempGCR=NM_GCR;
	NM_FORGET= 0;
	NM_NSR= 0x0010;
	NM_RSTCHAIN=0 ;
	for (int i=0; i< ncount; i++)
	{
		offset +=(i*recLen);
		NM_NCR= neurons[offset+1];
		for (int j=0; j<MaxLength; j++) NM_COMP=neurons[offset+2+j];
		NM_AIF= (neurons[offset + MaxLength +2]<<8)+neurons[offset + MaxLength+3];
		NM_MINIF= (neurons[offset + MaxLength+4]<<8)+neurons[offset + MaxLength+5];	
		NM_CAT= (neurons[offset + MaxLength+6]<<8)+neurons[offset + MaxLength+7];
	}
	NM_NSR=TempNSR; // set the NN back to its calling status
	NM_GCR=TempGCR;
	return(ncount);
}
