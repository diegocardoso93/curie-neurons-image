import cv2

QTD_PX_MAX = 2
PX_MAX_VAL = 255

img = cv2.imread('cucumber.png', cv2.IMREAD_GRAYSCALE)

#auto adjust image size
v_width = 250
v_height = 250
v_qtd_px_max = 999999


def generateHistogram(img):
	# 47 ~ 173
	k = 0
	for x in img:
		for i in x:
			if i>=47 and i<=173:
				hist[i-47] +=1
	return hist

def normalizeQuantity(hist):
	for i, item in enumerate(hist):
		hist[i] = 255 if item >= 255 else item
	return hist


while v_qtd_px_max > QTD_PX_MAX:

	img2 = cv2.resize(img, (v_width, v_height)) 

	hist = [0 for x in range(0,128)]

	hist = generateHistogram(img2)

	hist = normalizeQuantity(hist)

	print(hist)
	v_qtd_px_max = hist.count(PX_MAX_VAL)
	print(v_qtd_px_max)

	v_width = v_width - 1
	v_height = v_height - 1
	print(v_width, v_height)


cv2.imshow('Original', img)
cv2.imshow('Resize', img2)

cv2.waitKey(0)
cv2.destroyAllWindows()
