import cv2
import numpy as np

image = cv2.imread('./test.png')
print(image.shape)
#np.savetxt('./testimg.csv', image.reshape(640*480*3), fmt='%d')
