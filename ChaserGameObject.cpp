#include "ChaserGameObject.h"
#include "World.h"



Node::Node()
{
	parent = NULL;
	distance = 99999;
	isTerrain = false;
	neighbours = vector<Node*>();
	worldPos = glm::vec3();
	visited = false;
}


ChaserGameObject::ChaserGameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements, vector<vector<int>> grid):
	GameObject(entityPosition, entityTexture, entityNumElements)
{
	type = CHASER;
	team = ENEMIES;
	rowSize = grid.size();
	colSize = grid[0].size();
	dmgCooldown = 0.2f;
	nodeIndex = 1;

	makeNodeGrid(grid);

	pathfind() ? cout << "yes" << endl : cout << "no" << endl;
}



void ChaserGameObject::update(double deltaTime)
{
	Node* currentNode = path[nodeIndex];
	if (glm::distance(sv.position, currentNode->worldPos) > 0.01)
	{	
		sv.velocity = glm::normalize(currentNode->worldPos - sv.position) * (float)deltaTime * 1.0f;
		sv.position += sv.velocity;
	}
	else
	{
		if(nodeIndex != path.size() - 1)
			nodeIndex++;
		else
			shouldDie = true;
	}


	GameObject::update(deltaTime);
}

void ChaserGameObject::receiveDmg(int dmg)
{
	return; // don't receive damage
}

void ChaserGameObject::collide(int otherType, glm::vec3 normal, GameObject* otherObject)
{
	if (otherType == PLAYER)
		otherObject->receiveDmg(50);
}

void ChaserGameObject::makeNodeGrid(vector<vector<int>> grid)
{
	nodeGrid = vector<vector<Node*>>();
	for (int i = 0; i < rowSize; i++)
	{
		nodeGrid.push_back(vector<Node*>());
		for (int j = 0; j < colSize; j++)
		{
			Node* n = new Node();
			if (grid[i][j] > 0 && grid[i][j] < 100) n->isTerrain = true;
			//determine world pos
			glm::vec3 wPos;
			World::gridToWorldPos(i, j, &wPos);
			n->worldPos = wPos;

			nodeGrid[i].push_back(n);
		}
	}

	fillNeighbours();

	cout << nodeGrid.size() << " || " << nodeGrid[0].size() << endl;
}


bool ChaserGameObject::outOfBounds(int i, int j)
{
	return i < 0 || i > rowSize - 1 || j < 0 || j > colSize - 1;
}

void ChaserGameObject::fillNeighbours()
{
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			Node* n = nodeGrid[i][j];

			//determine neighbours
			!outOfBounds(i, j - 1) ? n->neighbours.push_back(nodeGrid[i][j - 1]) : NULL; //left
			!outOfBounds(i - 1, j) ? n->neighbours.push_back(nodeGrid[i - 1][j]) : NULL; //up
			!outOfBounds(i + 1, j) ? n->neighbours.push_back(nodeGrid[i + 1][j]) : NULL; //down
			!outOfBounds(i, j + 1) ? n->neighbours.push_back(nodeGrid[i][j + 1]) : NULL; //right
		}
	}
}

bool ChaserGameObject::pathfind()
{
	Node* start = nodeGrid[3][1]; //hardcoded values for level 2 only!
	Node* end = nodeGrid[20][1]; //hardcoded values for level 2 only!

	bool found = false;

	//Dijkstra's Algorithm
	start->distance = 0;
	pq.push_back(start);
	while (!pq.size() == 0)
	{
		Node* lowest = getMinimum();

		if (lowest == end)
		{
			found = true;
			break;
		}

		for (int i = 0; i < lowest->neighbours.size(); i++)
		{
			Node* n = lowest->neighbours[i];

			int tempDist = n->isTerrain ? lowest->distance + 1000 : lowest->distance + 1;
			if (tempDist < n->distance)
			{
				n->distance = tempDist;
				n->parent = lowest;

				//update pq
				if (!n->visited)
					pq.push_back(n);

				n->visited = true;
			}
		}

		pop(lowest);

	}


	//set our path
	Node* currentNode = end;
	vector<Node*> temp = vector<Node*>();

	while (currentNode->parent != NULL)
	{
		temp.push_back(currentNode);
		currentNode = currentNode->parent;
	}

	//put it in path variable in correct order
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		path.push_back(temp[i]);
	}

	return found;

}

void ChaserGameObject::pop(Node* n)
{
	for (int i = 0; i < pq.size(); i++)
	{
		if (n == pq[i])
		{
			pq.erase(pq.begin() + i);
			return;
		}
	}
}

Node* ChaserGameObject::getMinimum()
{
	Node* min = NULL;
	float minVal = 100000;
	for (int i = 0; i < pq.size(); i++)
	{
		if (pq[i]->distance < minVal)
		{
			min = pq[i];
			minVal = pq[i]->distance;
		}
	}

	return min;
}
