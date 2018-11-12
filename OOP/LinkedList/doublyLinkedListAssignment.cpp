Scores::~Scores() {	//destrutor
	while (!isEmpty()) {
		removeFront();
	}
}
bool Scores::isFull() const {
	return (counter == limit); 
}
void Scores::addAfter(Node* newNode) {
	if (!isEmpty()) {
		Node* temp = head;	//create pointer to head
		while (temp->points >= newNode->points) {	//find "perfect" spot
			if (temp->next == NULL || temp->next->points < newNode->points) {
				newNode->next = temp->next;
				temp->next = newNode;
				return;
			}
			temp = temp->next;	//traverse
		}
		//if first node is lower
		newNode->next = temp;
		head = newNode;
		return;
	}
	std::cout << "List is empty! \n";
}
void Scores::addFront(Node* newNode) {	//add first node
	newNode->next = head;
	head = newNode;
}
Node* Scores::lastNode() {	//return last node of the list
	if (!isEmpty()) {
		Node* temp = head;
		while (temp->next != NULL)
			temp = temp->next;	//traverse untill last node
		return temp;
	}
	std::cout << "List is empty! \n";
	return head;
}
void Scores::print() {
	if (!isEmpty()) {
		Node* temp = head;
		while (temp != NULL) {
			std::cout << temp->nickname << " : " << temp->points << std::endl;
			temp = temp->next;
		}
		return;
	}
	std::cout << "List is empty \n";
}
void Scores::removeFront() {
	if (!isEmpty()) {
		Node* temp = head;
		head = head->next;
		delete temp;
		return;
	}
	std::cout << "List is empty! \n";
}
void Scores::removeBack() {
	Node* temp = head;
