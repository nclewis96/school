A) For the nominal data, I used a modified version of KMeans called 
KModes. This modified version uses the nominal data in it's original 
form instead of translating it into numeric data. Because it is still
nominal data, the distance between a cluser and a data point is defined as 
the number of answers that are different. When changing the location of 
the Centroid, the Mode of the answers for each data field is found, 
and the Centroid's value is changed to that answer. Numeric data is 
treated the same as it normally is in KMeans.

B) In my algorithm, I assumed that if the majority of the ata is nominal, 
all of the data is nominal. Data sets that mix nominal and numeric would 
most likely not work correctly in my algorithm.

C) The data sets need to have a title row (which all 3 we were provided with do)
and a row of 0 and 1's before the data sets. 