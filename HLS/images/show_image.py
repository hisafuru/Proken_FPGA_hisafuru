import cv2
import numpy as np

image_array = np.loadtxt('./testimg_filter.csv')
image=image_array.reshape([478,638,3])
cv2.imwrite('./testimg_filter_r.png',image)
