
// Curie Neurons image KNN classify
// The patterns are arrays of length LEN composed of histogram of 32x32 fruit images
//
// The histograms are in 8bit grayscale between interval 47 ~ 173

#include "CurieNeurons.h"
#include "images.cpp"

CurieNeurons hNN;

#define CAT_CUCUMBER 1 
#define CAT_BANANA 2
#define CAT_APPLE 3
#define CAT_CARROT 4

int neuronsAvailable, neuronsCommitted, neuronSize;
int ncr, dist, cat, aif, nid, nsr;

#define LEN 128
byte pattern[LEN]; // values must range between 0-255. Upper byte is discarded by CM1K

#define K 3
int dists[K], cats[K], nids[K];

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for the serial port to open

  Serial.println("Neurons of Curie Image Classify");

  // Initialize the neurons
  hNN.begin();
  hNN.getNeuronsInfo( &neuronSize, &neuronsAvailable, &neuronsCommitted);
  Serial.print("Neuron size ="); Serial.println(neuronSize);
  Serial.print("Neurons available ="); Serial.println(neuronsAvailable);
  Serial.print("Neurons committed ="); Serial.println(neuronsCommitted);

  for (int i=0; i<LEN; i++){
    pattern[i] = histogram_cucumber[i];
  }
  neuronsCommitted = hNN.learn(pattern, LEN, CAT_CUCUMBER);

  for (int i=0; i<LEN; i++){
    pattern[i] = histogram_banana[i];
  }
  neuronsCommitted = hNN.learn(pattern, LEN, CAT_BANANA);

  for (int i=0; i<LEN; i++){
    pattern[i] = histogram_apple[i];
  }
  neuronsCommitted = hNN.learn(pattern, LEN, CAT_APPLE);

  for (int i=0; i<LEN; i++){
    pattern[i] = histogram_carrot[i];
  }
  neuronsCommitted = hNN.learn(pattern, LEN, CAT_CARROT);

  // Display the content of the committed neurons
  Serial.print("\nDisplay the committed neurons, count="); Serial.print(neuronsCommitted);
  byte model[neuronSize];
  for (int i=1; i<=neuronsCommitted; i++)
  {
      hNN.readNeuron(i, &ncr, model, &aif, &cat);
      Serial.print("\nneuron "); Serial.print(i); Serial.print("\tmodel=");
      for (int k=0; k<LEN; k++) { Serial.print(model[k]); Serial.print(", ");} 
      Serial.print("\tncr="); Serial.print(ncr);  
      Serial.print("\taif="); Serial.print(aif);     
      Serial.print("\tcat="); Serial.print(cat);
  }


  Serial.print("\n\nRecognizing a new pattern: ");
  for (int i=0; i<LEN; i++){
    pattern[i]=histogram_carrot_test[i];
  }
  for (int i=0; i<LEN; i++) { Serial.print(pattern[i]); Serial.print(", ");}
  int responseNbr=hNN.classify(pattern, LEN, K, dists, cats, nids);
  for (int i=0; i<responseNbr; i++)
  {
      Serial.print("\nFiring neuron "); Serial.print(nids[i]);
      Serial.print(", Category="); Serial.print(cats[i]);
      Serial.print(", at Distance="); Serial.print(dists[i]);
  }

}

void loop()
{

}

