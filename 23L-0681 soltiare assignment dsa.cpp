#include<iostream>
#include <iostream>
#include<chrono>
#include<algorithm>
#include<random>
using namespace std;
class Card {
public:
	char suit;
	char val;  // Holds 'A', '2'-'9', 'T', 'J', 'Q', 'K'
	bool not_hidden;

	Card(char s = 0, char v = 0) : suit(s), val(v), not_hidden(true) {}

	void flip() {
		not_hidden = !not_hidden;
	}

	int getRank() const {
		switch (val) {
		case 'A': return 1;
		case 'J': return 11;
		case 'Q': return 12;
		case 'K': return 13;
		default:  return (val >= '2' && val <= '9') ? val - '0' : 10; // 'T' for 10
		}
	}

	void displayCard() const {
		if (not_hidden) {
			switch (val) {
			case 'A': cout << "A"; break;
			case 'J': cout << "J"; break;
			case 'Q': cout << "Q"; break;
			case 'K': cout << "K"; break;
			case 'T': cout << "10"; break;
			default:  cout << val; break;
			}
			cout << suit;
		}
		else {
			cout << "[ ]";
		}
	}

	bool isFaceUp() const {
		return not_hidden;
	}

	bool isRed() const {
		return (suit == 'H' || suit == 'D'); // Hearts, Diamonds
	}

	bool isBlack() const {
		return (suit == 'S' || suit == 'C'); // Spades, Clubs
	}

	friend ostream& operator<<(ostream& out, Card* card) {
		if (card->isFaceUp()) {
			if (card->val == 'T') { // Handle 10 separately for alignment
				out << "10" << card->suit;
			}
			else {
				out << card->val << card->suit;
			}
		}
		else {
			out << "[Hidden]";
		}
		return out;
	}
	void setfaceup() {
		not_hidden = true;
	}
};
template<class T>
class List
{
private:
	class Node {
	public:
		Node* next;
		Node* prev;
		//Card data;
		T data;
		Node() {
			next = nullptr;
			prev = nullptr;
		}
		Node(T d, Node* n = nullptr, Node* p = nullptr) {
			data = d;
			next = n;
			prev = p;
		}
	};
	Node* head;
	Node* tail;
	int size;// check the number of cards in each coulmn
public:
	class iterator {
		friend class List;
		Node* curr;//This will tell us about the curr node at the which it is pointing
		iterator(Node* p)
		{
			curr = p;
		}
	public:
		iterator() {
			curr = nullptr;
		}
		iterator& operator++() {
			curr = curr->next;
			return *this;
		}
		iterator operator++(int) {
			iterator obj = *this;
			curr = curr->next;
			return obj;
		}
		iterator& operator--() {
			curr = curr->prev;
			return *this;
		}
		iterator& operator--(int) {
			iterator obj = *this;
			curr = curr->prev;
			return obj;
		}
		T& operator* ()
		{
			return curr->data;
		}
		bool operator!=(const iterator& rhs) const
		{
			return curr != rhs.curr;
		}
		bool operator==(const iterator& rhs) const
		{
			return curr == rhs.curr;
		}
	};
	List()
	{
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
		size = 0;
	}
	iterator begin() const {
		iterator it(head->next);
		return it;
	}
	iterator end() const {
		iterator temp(tail);
		return temp;
	}
	bool listisempty() {
		if (head->next == tail) {
			return true;
		}
		else
			return false;
	}
	void InsertatHead(T c) {
		Node* temp = new Node(c, head->next, head);
		head->next->prev = temp;
		head->next = temp;
		size++;
	}
	void Insertatend(T c) {
		Node* temp = new Node(c, tail, tail->prev);
		if (head->next == tail) {
			Node* t = new Node(c, tail, head);
			head->next = tail;
			tail->prev = head;
		}
		tail->prev->next = temp;
		tail->prev = temp;
		size++;
	}
	void RemoveatHead() {
		if (head == nullptr) {
			// List is already empty
			return;
		}

		Node* temp = head->next; // the node to be removed

		// If there's only one element (head->next == tail), make sure to handle it
		if (temp == tail) {
			delete temp; // remove the only element
			head->next = tail; // update pointers
			tail->prev = head;
			return;
		}

		// Otherwise, proceed with normal removal
		head->next = temp->next;
		if (temp->next != nullptr) {
			temp->next->prev = head;
		}

		delete temp; // free the removed node
	}
	void removeCard()
	{
		Node* temp = tail->prev;
		temp->prev->next = tail;
		tail->prev = temp->prev;
	}
	void display()
	{
		iterator obj = begin();
		for (; obj != end(); obj++) {
			cout << *obj << " " << endl;
		}
	}
	T getdata() {
		if (!listisempty()) {
			return head->next->data;
		}
	}
	T peek() {
		if (!listisempty()) {
			return tail->prev->data;  // Assuming tail has a prev pointer to the last real node.
		}
		return nullptr;  // If the list is empty.
	}
	void Removetarget(T card) {
		Node* current = head->next;
		while (current != tail && current->data != card) {
			current = current->next;
		}
		if (current != tail) { // Found the card
			current->prev->next = current->next;
			current->next->prev = current->prev;
			delete current;  // Assuming dynamic allocation.
			size--;
		}
	}
	void add(T c) {
		if (c != nullptr) {
			Insertatend(c);
		}
		else {
			cout << "Error: Attempt to add a null card" << endl;
		}
	}
	int getlistsize() {
		return size;
	}
	static bool subList(iterator src, iterator des, iterator srctail, List<T>& sourceList, List<T>& destList, int numCards) {
		if (src.curr != nullptr && des.curr != nullptr && src.curr != sourceList.head && des.curr != destList.tail) {
			Node* temp = src.curr;
			Node* sourcetail = srctail.curr;

			// Disconnect the sublist from the source
			temp->prev->next = sourcetail;
			sourcetail->prev = temp->prev;

			// Connect the sublist to the destination
			Node* accessdestination = des.curr;
			Node* lastNode = temp;
			for (int i = 1; i < numCards && lastNode->next != sourcetail; ++i) {
				lastNode = lastNode->next;
			}

			Node* tempNext = accessdestination->next;
			accessdestination->next = temp;
			temp->prev = accessdestination;
			lastNode->next = tempNext;
			tempNext->prev = lastNode;

			// Update sizes
			sourceList.size -= numCards;
			destList.size += numCards;

			return true;
		}
		return false;
	}
};
template<class T>
class Stack {
private:
	List<T>obj;
	int size;
public:
	Stack() {
		size = 0;
	}
	bool Isempty() {
		if (obj.listisempty()) {
			return true;
		}
		else {
			return false;
		}
	}
	void push(T c)
	{
		obj.InsertatHead(c);
		size++;
	}
	bool pop(T& card) {//passed by refrence so data is not lost
		if (!Isempty())
		{
			card = obj.getdata();
			obj.RemoveatHead();
			size--;
			return true;
		}
		else
			return false;
	}
	bool top(T& pata) {
		if (!Isempty()) {
			pata = obj.getdata();
			return true;
		}
		else
			return false;
	}
	int getsize() {
		return size;
	}
};
class Command {
public:
	//int destfoundation;
	int cardquantity;
	int destinationcoulmn;
	int sourcecoulmn;
	int fromwhere;//0 matlb coulmn,1 hai to stock,2 hai wastepile
	int towhere;// if 0 to movement from tableu sy tableu 1 hai to waste pile
	Command() { }
	Command(int c, int d, int s, int f, int t) {
		//destfoundation = destf;
		cardquantity = c;
		destinationcoulmn = d;
		sourcecoulmn = s;
		fromwhere = f;
		towhere = t;
	}
};
class Game
{
	Card** deck;
	int decksize = 52;
	Stack<Card*>stock;
	Stack<Card*>foundation[4];
	List<Card*>tableau[7];
	Stack<Card*>waste;
	Stack<Command>undo;
public:
	Game() :deck(nullptr) {
		initializegame();
		shuffleDeck();
		dealcards();
	}
	void initializegame() {
		deck = new Card * [decksize];//Initialize to 52 objects
		const int suitSize = 4;
		const int cardssize = 13;
		const char suits[] = { 'H', 'D', 'C', 'S' };  // Hearts, Diamonds, Clubs, Spades
		const char values[] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
		int index = 0;
		for (int i = 0; i < suitSize; i++) {
			for (int j = 0; j < cardssize; j++) {
				deck[index] = new Card(suits[i], values[j]);
				deck[index]->flip();
				index++;
			}
		}
	}
	void shuffleDeck() {
		random_device rd;
		mt19937 g(rd());

		for (int i = decksize - 1; i > 0; i--) {
			uniform_int_distribution<int> dist(0, i);
			int j = dist(g);
			Card* temp = deck[i];
			deck[i] = deck[j];
			deck[j] = temp;
		}
	}
	// the function below will used to make lists
	void dealcards() {
		int index = 0;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j <= i; j++) {
				Card* ptr = deck[index++];
				ptr->not_hidden = (j == i); // Flip only the top card face up
				tableau[i].Insertatend(ptr);
			}
		}
		// After making list the rest of the cards are pushed into stock
		while (index < decksize) {
			stock.push(deck[index++]);
		}
	}
	void resetStock() {
		Card* card = nullptr;
		while (waste.pop(card)) {  // Pop fills card and returns true if successful passed by refrence so returns accoridng to it
			card->not_hidden = false;  // Flip card face down
			stock.push(card);          // Push back onto the stock
		}
	}
	void move_from_waste_to_stock() {
		if (stock.Isempty()) {
			resetStock();
		}
	}
	void move_from_stock_to_waste() {
		/*if (stock.Isempty()) {
			resetStock();
		}*/
		//else {
		Card* card = nullptr;
		bool flag = stock.pop(card);
		if (flag) {
			card->not_hidden = true;
			waste.push(card);
			//	card = nullptr;
			////}
		}
	}
	bool canMoveToFoundation(Card* pata, int index)
	{
		Card* topreader = nullptr;
		bool check = foundation[index].top(topreader);
		if (!check) { // Check if foundation is empty
			return pata->val == 'A'; // Only an Ace can start a foundation
		}
		else {
			return (pata->suit == topreader->suit && pata->getRank() == topreader->getRank() + 1);
		}
	}
	bool moveFromWasteToFoundation(int foundationIndex) {
		if (waste.Isempty()) {
			return false;
		}
		Card* store = nullptr;
		bool checker = waste.top(store);  // Get the top card without removing it

		if (checker && canMoveToFoundation(store, foundationIndex)) {
			bool removeresult = waste.pop(store);  // Remove the card from the waste
			if (removeresult) {
				foundation[foundationIndex].push(store);  // Add the card to the foundation
				return true;
			}
		}
		return false;
	}
	bool move_from_coulmn_to_foundation(int tableauIndex, int foundationIndex) {
		if (tableau[tableauIndex].listisempty()) return false;
		Card* card = tableau[tableauIndex].peek(); // Look at the top card without removing
		if (canMoveToFoundation(card, foundationIndex)) {
			tableau[tableauIndex].Removetarget(card);
			if (tableau[tableauIndex].getlistsize() > 0) {
				tableau[tableauIndex].peek()->setfaceup();
			}
			//tableau[tableauIndex].peek()->setfaceup();
			foundation[foundationIndex].push(card);
			return true;
		}
		return false;
	}
	bool canMoveToTableau(Card* card, int index) {
		Card* situation = tableau[index].peek(); // Retrieve the top card from the target tableau column
		if (situation == nullptr) {
			// Generally, only Kings can be placed on empty tableau columns.
			// If your rule allows placing any card on an empty tableau, adjust accordingly.
			return card->val == 'K';
		}
		// Check if the cards follow alternating colors and the rank is exactly one less than the card on the tableau
		if ((situation->isBlack() != card->isBlack() && situation->getRank() == card->getRank() + 1) ||
			(situation->isRed() != card->isRed() && situation->getRank() == card->getRank() + 1)) {
			return true;
		}
		return false;
	}
	bool moveBetweenTableau(int fromIndex, int toIndex) {
		//Moving in coulmns
		if (tableau[fromIndex].listisempty()) {
			return false;
		}
		Card* card = tableau[fromIndex].peek();
		if (card != nullptr && canMoveToTableau(card, toIndex))
		{
			tableau[fromIndex].Removetarget(card);
			tableau[toIndex].add(card);
			if (tableau[fromIndex].getlistsize() > 1||tableau[fromIndex].getlistsize()==1) {
				tableau[fromIndex].peek()->setfaceup();
			}
			return true;
		}
		return false;
	}
	bool cardsmovement(int fromIndex, int toIndex, int numofCards) {
		if (tableau[fromIndex].listisempty() || numofCards <= 0) {
			return false;
		}
		if (tableau[fromIndex].getlistsize() >= numofCards) {
			List<Card*>::iterator source = tableau[fromIndex].end();
			List<Card*>::iterator sourcetail = tableau[fromIndex].end();
			--source; // Move to the last actual node
			for (int i = 1; i < numofCards; i++) {
				if (!(*source)->isFaceUp()) {
					return false;
				}
				--source;
			}
			Card* ptr = *source;
			if (canMoveToTableau(ptr, toIndex)) {
				List<Card*>::iterator destination = tableau[toIndex].end();
				--destination; // Move to the last actual node
				// Move the cards and update both source and destination lists
				bool success = List<Card*>::subList(source, destination, sourcetail, tableau[fromIndex], tableau[toIndex], numofCards);
				// Flip the new top card in the source column if it's face down
				if (success && !tableau[fromIndex].listisempty()) {
					Card* newTopCard = tableau[fromIndex].peek();
					if (newTopCard && !newTopCard->isFaceUp()) {
						newTopCard->flip();
					}
				}
				return success;
			}
		}
		return false;
	}
	bool move_from_waste_to_coulmn(int coulmnnumber) {
		Card* ptr = nullptr;
		bool firstcard = waste.top(ptr); // Only first card can be moved from waste to tableau

		// Handle the case of an empty column
		if (tableau[coulmnnumber].listisempty()) {
			if (ptr && ptr->val=='K') {
				Card* ptr2 = nullptr;
				bool flag = waste.pop(ptr2);
				if (flag) {
					tableau[coulmnnumber].add(ptr2);
					return true;
				}
			}
			return false;
		}
		Card* coulmn = tableau[coulmnnumber].peek();
		if (firstcard && coulmn != nullptr) {
			if ((ptr->isBlack() != coulmn->isBlack() && ptr->getRank() < coulmn->getRank()) ||
				(ptr->isRed() != coulmn->isRed() && ptr->getRank() < coulmn->getRank()))
			{
				bool flag = waste.pop(ptr);
				tableau[coulmnnumber].add(ptr);
				return true;
			}
		}
		else
		{
			//ste.push(ptr);
			return false;
		}
	}
	void excecutecommand(Command& cmd) {
		bool flag = false;
		if (cmd.fromwhere == 0 && cmd.towhere == 0) {//coulmn to coulmn movement
			flag = moveBetweenTableau(cmd.sourcecoulmn, cmd.destinationcoulmn);
			if (cmd.cardquantity > 1) {
				flag = cardsmovement(cmd.sourcecoulmn, cmd.destinationcoulmn, cmd.cardquantity);
			}
		}
		if (cmd.fromwhere == 1 && cmd.towhere == 2) {
			move_from_stock_to_waste();
			flag = true;
		}
		if (cmd.fromwhere == 2 && cmd.towhere == 1) {
			move_from_waste_to_stock();
			flag = true;
		}
		if (cmd.fromwhere == 2 && cmd.towhere == 0) {
			flag = move_from_waste_to_coulmn(cmd.destinationcoulmn);
		}
		if (cmd.fromwhere == 2 && cmd.towhere == 3) {
			flag = moveFromWasteToFoundation(cmd.destinationcoulmn);//adjust values according to the foundation index
		}
		if (cmd.fromwhere == 0 && cmd.towhere == 3) {
			flag = move_from_coulmn_to_foundation(cmd.sourcecoulmn, cmd.destinationcoulmn);
		}
		if (flag) {
			undo.push(cmd);
		}
	}
	void undone() {
		Command ptr;
		if (!undo.Isempty()) {
			bool flag = undo.pop(ptr);
			if (flag) {
				reverseCommand(ptr);
			}
		}
	}
	//////////////////////////////////////////////
	//Undo part
	void reverseMoveFromStockToWaste() {
		Card* card = nullptr;
		if (waste.pop(card)) {
			stock.push(card);
		}
	}
	bool reverseMoveFromFoundationToWaste(int foundationIndex) {
		Card* card = nullptr;
		if (foundation[foundationIndex].pop(card)) {
			waste.push(card);
			return true;
		}
		return false;
	}
	bool reverseMoveFromFoundationToColumn(int foundationIndex, int columnIndex) {
		Card* card = nullptr;
		if (foundation[foundationIndex].pop(card)) {
			tableau[columnIndex].add(card);
			return true;
		}
		return false;
	}
	bool reverseMoveFromColumnToWaste(int columnIndex) {
		Card* card = nullptr;
		if (!tableau[columnIndex].listisempty()) {
			card = tableau[columnIndex].peek();
			tableau[columnIndex].Removetarget(card);
			waste.push(card);
			return true;
		}
		return false;
	}
	bool reversemovebetweentableau(int fromIndex, int toIndex) {//from index is destination and to index is source
		if (tableau[fromIndex].listisempty()) {
			return false;
		}
		Card* card = tableau[fromIndex].peek();
		if (card != nullptr)
		{
			tableau[fromIndex].Removetarget(card);
			tableau[toIndex].add(card);
			return true;
		}
		return false;
	}

	bool reversecardsmovement(int fromIndex, int toIndex, int numofCards) {
		if (tableau[fromIndex].listisempty() || numofCards <= 0) {
			return false;
		}
		if (tableau[fromIndex].getlistsize() >= numofCards) {
			List<Card*>::iterator source = tableau[fromIndex].end();
			List<Card*>::iterator sourcetail = tableau[fromIndex].end();
			--source; // Move to the last actual node
			for (int i = 1; i < numofCards; i++) {
				if (!(*source)->isFaceUp()) {
					return false;
				}
				--source;
			}
			Card* ptr = *source;
			List<Card*>::iterator destination = tableau[toIndex].end();
			--destination; // Move to the last actual node
			// Move the cards and update both source and destination lists
			bool success = List<Card*>::subList(source, destination, sourcetail, tableau[fromIndex], tableau[toIndex], numofCards);
			// Flip the new top card in the source column if it's face down
			if (success && !tableau[fromIndex].listisempty()) {
				Card* newTopCard = tableau[fromIndex].peek();
				if (newTopCard && !newTopCard->isFaceUp()) {
					newTopCard->flip();
				}
			}
			return success;
		}
		return false;
	}
	void reverseCommand(Command& cmd) {
		if (cmd.towhere == 0 && cmd.fromwhere == 0) {  // Reverse column to column movement
			reversemovebetweentableau(cmd.destinationcoulmn, cmd.sourcecoulmn);
			if (cmd.cardquantity > 1) {
				reversecardsmovement(cmd.destinationcoulmn, cmd.sourcecoulmn, cmd.cardquantity);
			}
		}
		else if (cmd.fromwhere == 1 && cmd.towhere == 2) {
			reverseMoveFromStockToWaste();
		}
		else if (cmd.towhere == 0 && cmd.fromwhere == 2) {
			reverseMoveFromColumnToWaste(cmd.destinationcoulmn);
		}
		else if (cmd.towhere == 3 && cmd.fromwhere == 2) {
			reverseMoveFromFoundationToWaste(cmd.destinationcoulmn);
		}
		else if (cmd.fromwhere == 0 && cmd.towhere == 3) {
			reverseMoveFromFoundationToColumn(cmd.destinationcoulmn, cmd.sourcecoulmn);
		}
	}
	bool isGameWon() {
		for (int i = 0; i < 4; i++) {
			if (foundation[i].getsize() != 13) return false; // Each foundation should have 13 cards
		}
		return true;
	}
	void displayGame()
	{
		// Display stock and waste piles
		cout << "Stock [ ";
		if (stock.Isempty()) {
			cout << "Empty";
		}
		else {
			cout << stock.getsize() << " cards";
		}
		cout << " ]\tWaste [ ";
		if (waste.Isempty()) {
			cout << "Empty";
		}
		else {
			// Display the top card of the waste
			Card* dis = nullptr;
			if (waste.top(dis) && dis != nullptr) {
				dis->displayCard();
				cout << " (" << waste.getsize() << " cards)";
			}
			else {
				cout << "Empty";
			}
		}
			cout << endl;
			cout << " ]" << endl;
			// Display foundation piles
			cout << "Foundation 1 [ ";
			if (foundation[0].Isempty()) {
				cout << "Empty";
			}
			else {
				Card* ptr = nullptr;
				if (foundation[0].top(ptr) && ptr != nullptr) {
					ptr->displayCard();
					cout << " (" << foundation[0].getsize() << " cards)";
				}
			}
			cout << " ]\tFoundation 2 [ ";
			if (foundation[1].Isempty()) {
				cout << "Empty";
			}
			else {
				Card* ptr = nullptr;
				if (foundation[1].top(ptr) && ptr != nullptr) {
					ptr->displayCard();
					cout << " (" << foundation[1].getsize() << " cards)";
				}
			}
			cout << " ]\tFoundation 3 [ ";
			if (foundation[2].Isempty()) {
				cout << "Empty";
			}
			else {
				Card* ptr = nullptr;
				if (foundation[2].top(ptr) && ptr != nullptr) {
					ptr->displayCard();
					cout << " (" << foundation[2].getsize() << " cards)";
				}
			}
			cout << " ]\tFoundation 4 [ ";
			if (foundation[3].Isempty()) {
				cout << "Empty";
			}
			else {
				Card* ptr = nullptr;
				if (foundation[3].top(ptr) && ptr != nullptr) {
					ptr->displayCard();
					cout << " (" << foundation[3].getsize() << " cards)";
				}
			}
			cout << " ]" << endl;
			cout << endl;

			for (int i = 0; i < 7; i++) {
				cout << "Column " << (i + 1) << " [ ";
				if (tableau[i].listisempty()) {
					cout << "Empty ]";
				}
				else {
					cout << tableau[i].getlistsize() << " cards ]: ";
					for (List<Card*>::iterator it = tableau[i].begin(); it != tableau[i].end(); ++it) {
						Card* card = *it;
						card->displayCard();
						if (it != --tableau[i].end()) {
							cout << ", ";
						}
					}
				}
				cout << endl;
			}
	}
};
		int main() {
			Game obj;
			obj.displayGame();  // Display initial state of the game

			int numofcard, destination, source, from, where;

			cout << "WELCOME TO SOLITAIRE" << endl;
			cout << "Keys: Column move - press 0, Stock move - press 1, Waste move - press 2, Foundation move - press 3" << endl;
			cout << "Enter -1 at any prompt to undo the last move." << endl;

			while (!obj.isGameWon()) {
				cout << "Enter number of cards (or -1 to undo): ";
				cin >> numofcard;
				if (numofcard == -1) {
					obj.undone();
					obj.displayGame();
					continue;
				}

				cout << "Enter destination column (or -1 to undo): ";
				cin >> destination;
				if (destination == -1) {
					obj.undone();
					obj.displayGame();
					continue;
				}

				cout << "Enter source column/index (or -1 to undo): ";
				cin >> source;
				if (source == -1) {
					obj.undone();
					obj.displayGame();
					continue;
				}

				cout << "Enter from where you want to move (or -1 to undo): ";
				cin >> from;
				if (from == -1) {
					obj.undone();
					obj.displayGame();
					continue;
				}

				cout << "Enter to where you want to move (or -1 to undo): ";
				cin >> where;
				if (where == -1) {
					obj.undone();
					obj.displayGame();
					continue;
				}

				Command moveCmd1(numofcard, destination, source, from, where);
				obj.excecutecommand(moveCmd1);
				obj.displayGame();
			}

			cout << "Congratulations, you've won the game!" << endl;
			return 0;
		}