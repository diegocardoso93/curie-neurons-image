import cv2

img = cv2.imread('cucumber.png',cv2.IMREAD_GRAYSCALE)

# 47 ~ 173
k = 0
hist = [0 for x in range(0,128)]
for x in img:
	for i in x:
		if i>=47 and i<=173:
			hist[i-47] +=1

print(hist)

print(*img)

cv2.imshow('cucumber', img)
cv2.waitKey(0)
cv2.destroyAllWindows()