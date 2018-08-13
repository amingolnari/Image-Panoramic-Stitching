import cv2
import numpy as np
import time
import glob

def ShowStitchImage(images):
    startTime = time.clock()
    stitcher = cv2.createStitcher()
    res, outImage = stitcher.stitch(images)
    endTime = time.clock()
    if res == 0:
        print('Processing Time : ' + str(endTime - startTime) + ' sec')
        for i in range(np.array(images).size):
            images[i] = cv2.resize(images[i], (200,200))
        together = np.hstack(images)
        cv2.namedWindow("Show Together Images", 0)
        cv2.resizeWindow("Show Together Images", 600, 200)
        cv2.imshow("Show Together Images", together)
        cv2.namedWindow("Stitch Result", 0)
        cv2.resizeWindow("Stitch Result", 600, 400)
        cv2.imshow("Stitch Result", outImage)
        cv2.imwrite('TogetherPY.jpg', together)
        cv2.imwrite('StitchPY.jpg', outImage)
        cv2.waitKey()
    else :
        print('\nStitching failed !!')
    return

def readFromPath(path):
    images = []
    filesName = glob.glob(path)
    for name in filesName:
        images.append(cv2.imread(name))
        print(name)
    return images

def main():
    path = "Pano Images/qazvin*"
    images = readFromPath(path)
    ShowStitchImage(images)
    return

if __name__ == "__main__":
    main()
