# Image-Analysis
Image Analisys School Project (Qt, C++)

### Features

- **Convert image to grayscale**
- **Histogram equalization**
	- auto
	- manual
- **Image binarization**
	- auto - *Otsu's method*
	- manual
- **Pattern recognition**
	- recognize class - *Hu's moments + KNN algorithm*
		- select *K* neighbors
		- select distance metric
			- absolute - *| x - x' |*
			- euclidean - *( x - x' ) ^ 2*
			- infinite - *| x > x' |*
	- add image
		- insert class name or create a new one


### Preview

<center>

<table width="90%">
	<tr>
		<td>
			<img src="./screenshots/grayscale.png" width="100%"/>
		</td>
		<td>
			<img src="./screenshots/equalization.png" width="100%"/>
		</td>
	</tr>
	<tr>
		<td>
			<img src="./screenshots/binarization.png" width="100%"/>		</td>
		<td>
			<img src="./screenshots/recognition.png" width="100%"/>
		</td>
	</tr>
	<tr></tr>
</table>

</center>