#pragma once
#include "GameObject.h"
#include <vector>

using namespace std;

class Node
{
	friend class ChaserGameObject;
public:
	Node();
private:
	vector<Node*> neighbours;
	Node* parent;
	int distance;
	bool isTerrain;
	bool visited;
	glm::vec3 worldPos;

};

class ChaserGameObject :
	public GameObject
{
public:
	ChaserGameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements, vector<vector<int>> grid);

	void update(double deltaTime) override;

	virtual void receiveDmg(int dmg) override;

	virtual void collide(int otherType, glm::vec3 normal, GameObject* otherObject) override;

private:
	vector<Node*> path;
	vector<vector<Node*>> nodeGrid;
	vector<Node*> pq;

	bool pathfind();
	bool outOfBounds(int i, int j);
	void makeNodeGrid(vector<vector<int>> grid);
	void fillNeighbours();
	Node* getMinimum();
	void pop(Node* n);

	int rowSize;
	int colSize;
	int nodeIndex;
};

