"""

"""

import numpy as np

class BezierCurve():
	"""
	
	"""
	def __init__(self, degree: int, dimensions: int) -> None:
		"""
		
		"""
		self.DEGREE = degree
		self.DIMENSIONS = dimensions

		self.control_points: np.ndarray = None