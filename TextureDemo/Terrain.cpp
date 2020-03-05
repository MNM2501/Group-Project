#include "Terrain.h"




/*	Grid values to texture information

	0 - Nothing
	1 - grass tile
	2 - dirt tile

	--------------------------------------
*/

Terrain::Terrain(int _rowSize, int _colSize, int** entityGrid, std::vector<GLuint> entityTextures, GLint entityNumElements)
{
	grid = entityGrid;
	textures = entityTextures;
	numElements = entityNumElements;

	//dimensions
	rowSize = _rowSize;
	colSize = _colSize;
}


//renders terrain
void Terrain::render(Shader& shader)
{
	return;
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			//position of tile
			glm::vec3 position = glm::vec3(j, i - 5, 0);

			// Bind the entities texture
			glBindTexture(GL_TEXTURE_2D, textures[grid[i][j]]);

			// Setup the transformation matrix for the shader
			// TODO: Add different types of transformations
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);


			// Set the transformation matrix in the shader
			// TODO: Multiply your new transformations to make the transformationMatrix
			glm::mat4 transformationMatrix = translationMatrix;
			shader.setUniformMat4("transformationMatrix", transformationMatrix);

			// Draw the entity
			glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
		}
	}
}



