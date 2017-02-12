## Image Classify With CurieNeurons Pattern Matching Engine
Using General Vision Lib / Arduino 101 with Intel Curie
with KNN classify

Training images:

![Image of cucumber](https://github.com/Fyrewell/CurieNeuronsImage/blob/master/cucumber.png) 
![Image of banana](https://github.com/Fyrewell/CurieNeuronsImage/blob/master/banana.png) 
![Image of apple](https://github.com/Fyrewell/CurieNeuronsImage/blob/master/apple.png) 
![Image of carrot](https://github.com/Fyrewell/CurieNeuronsImage/blob/master/carrot.png) 

The image test is:
![Image of carrot_test](https://github.com/Fyrewell/CurieNeuronsImage/blob/master/carrot_test.png)


rgb_to_grayscale.py requires cv lib, used to convert RGB888 to grayscale and generate histograms 

## Output
```
Neurons of Curie Image Classify
Neuron size =128
Neurons available =128
Neurons committed =0

Display the committed neurons, count=4
neuron 1	model=0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 1, 1, 2, 2, 1, 5, 5, 2, 7, 4, 9, 4, 9, 7, 6, 9, 6, 6, 6, 10, 5, 9, 6, 9, 13, 8, 12, 8, 10, 4, 8, 6, 10, 10, 5, 9, 15, 7, 11, 9, 9, 8, 9, 6, 12, 6, 7, 8, 10, 8, 11, 12, 12, 19, 11, 7, 12, 17, 6, 14, 19, 12, 16, 14, 3, 15, 16, 18, 15, 21, 13, 12, 17, 13, 20, 18, 12, 17, 11, 16, 12, 17, 15, 17, 11, 8, 8, 9, 9, 6, 8, 3, 5, 7, 3, 5, 6, 4, 9, 8, 3, 6, 4, 4, 5, 5, 4, 2, 1, 2, 4, 3, 1, 3, 1, 0, 	ncr=1	aif=467	cat=1
neuron 2	model=0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 1, 2, 0, 0, 1, 0, 0, 3, 1, 1, 3, 1, 2, 1, 1, 0, 0, 1, 7, 3, 6, 7, 4, 1, 4, 8, 8, 5, 4, 4, 7, 7, 6, 10, 7, 10, 6, 4, 10, 8, 12, 3, 5, 9, 8, 10, 10, 10, 8, 11, 12, 10, 21, 10, 5, 9, 20, 13, 8, 6, 6, 10, 11, 25, 13, 23, 21, 14, 7, 15, 13, 15, 20, 12, 17, 13, 21, 14, 13, 28, 16, 22, 12, 13, 15, 6, 14, 17, 14, 19, 21, 14, 16, 8, 8, 11, 6, 10, 9, 16, 7, 11, 4, 7, 5, 10, 6, 3, 4, 7, 3, 5, 1, 0, 0, 3, 1, 0, 	ncr=1	aif=473	cat=2
neuron 3	model=3, 4, 4, 2, 3, 2, 5, 9, 2, 1, 2, 3, 3, 3, 5, 7, 5, 9, 2, 4, 9, 3, 1, 8, 4, 4, 11, 3, 9, 7, 5, 3, 4, 6, 8, 4, 7, 6, 5, 3, 8, 8, 19, 14, 8, 5, 5, 13, 10, 7, 9, 12, 14, 10, 11, 11, 18, 10, 11, 14, 13, 9, 12, 8, 7, 11, 8, 13, 12, 10, 15, 17, 16, 10, 14, 12, 16, 20, 21, 14, 26, 12, 30, 19, 12, 12, 14, 24, 14, 20, 14, 17, 6, 5, 8, 9, 8, 7, 8, 8, 7, 4, 10, 2, 6, 6, 2, 5, 3, 5, 2, 1, 3, 3, 5, 2, 2, 2, 2, 0, 0, 2, 1, 0, 1, 0, 0, 0, 	ncr=1	aif=458	cat=3
neuron 4	model=1, 0, 0, 0, 0, 3, 2, 1, 2, 2, 1, 4, 3, 1, 7, 6, 4, 2, 6, 6, 9, 4, 5, 8, 11, 4, 8, 11, 9, 14, 9, 7, 6, 12, 7, 7, 9, 13, 7, 10, 9, 4, 10, 5, 9, 5, 3, 11, 9, 8, 13, 14, 9, 8, 10, 10, 7, 12, 13, 12, 12, 11, 12, 5, 10, 6, 8, 9, 5, 4, 5, 10, 5, 12, 7, 13, 17, 21, 19, 18, 16, 11, 21, 19, 12, 17, 13, 16, 13, 24, 25, 29, 18, 17, 19, 23, 22, 25, 13, 12, 5, 6, 3, 5, 3, 2, 3, 1, 5, 6, 2, 2, 0, 0, 0, 1, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 	ncr=1	aif=458	cat=4

Recognizing a new pattern: 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 3, 4, 8, 4, 6, 2, 7, 4, 10, 12, 9, 7, 13, 11, 8, 5, 15, 12, 12, 17, 11, 15, 17, 10, 12, 12, 12, 9, 9, 18, 14, 14, 9, 13, 7, 7, 11, 8, 9, 10, 8, 10, 9, 5, 8, 12, 5, 7, 9, 7, 10, 12, 3, 5, 11, 9, 6, 6, 10, 13, 8, 5, 7, 9, 13, 14, 16, 21, 19, 14, 18, 13, 20, 17, 16, 18, 13, 17, 16, 20, 16, 21, 23, 34, 11, 9, 7, 5, 3, 3, 4, 5, 5, 2, 1, 3, 0, 2, 1, 4, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
Firing neuron 4, Category=4, at Distance=414
Firing neuron 1, Category=1, at Distance=465
```
