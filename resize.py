import cv2
import numpy as np
import time

# Load the image
image = cv2.imread('G178_2-1080.BMP')

# Define the new size (for example, half the original size)
new_size = (image.shape[1] // 2, image.shape[0] // 2)

# Resize using INTER_NEAREST
start_time = time.time()
for _ in  range(1000):
    resized_nearest = cv2.resize(image, new_size, interpolation=cv2.INTER_NEAREST)
time_nearest = (time.time() - start_time) * 1000

# Resize using INTER_LINEAR
start_time = time.time()
for _ in  range(1000):
    resized_linear = cv2.resize(image, new_size, interpolation=cv2.INTER_LINEAR)
time_linear = (time.time() - start_time) * 1000

# Resize using INTER_CUBIC
start_time = time.time()
for _ in  range(1000):
    resized_cubic = cv2.resize(image, new_size, interpolation=cv2.INTER_CUBIC)
time_cubic = (time.time() - start_time) * 1000

# Print timings
print(f'Time taken for 1000 iterations using INTER_NEAREST: {time_nearest:.2f} ms')
print(f'Time taken for 1000 iterations using INTER_LINEAR: {time_linear:.2f} ms')
print(f'Time taken for 1000 iterations using INTER_CUBIC: {time_cubic:.2f} ms')

# Save the resized images
cv2.imwrite('resized_nearest.bmp', resized_nearest)
cv2.imwrite('resized_linear.bmp', resized_linear)
cv2.imwrite('resized_cubic.bmp', resized_cubic)
