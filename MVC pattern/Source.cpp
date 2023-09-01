#include <iostream>

using namespace std;

class Task {
	string task;
	bool state;
public:
	Task() : task(""), state(false) {};

	Task(string t, bool s) : task(t), state(s) {};

	void edit(bool state, string task = "") {
		this->state = state;
		if (task != "") {
			this->task = task;
		}
	}

	void operator()(Task& t) {
		this->task = t.task;
		this->state = t.state;
	}

	friend ostream& operator<<(ostream& out,const Task& t) {
		out << t.task << "\tstate : ";
		if (t.state == false)out << "not done";
		else { out << "done"; }
		return out;
	}
};

class Model {
	Task* tasks;
	int size;
public:
	Model(initializer_list<Task> list) {
		size = list.size();
		tasks = new Task[size];
		int i = 0;
		for (Task task : list) {
			tasks[i++] = task;
		}
	}

	void addTask(string task, bool state) {
		Task* na = new Task[size + 1];
		for (int i = 0; i < size; i++) {
			na[i] = tasks[i];
		}
		na[size++].edit(state, task);
		if (tasks != nullptr)delete[] tasks;
		tasks = na;
	}

	void deleteTask(int pos = 1) {
		pos--;
		Task* na = new Task[size - 1];
		for (int i = 0, j = 0; j < size; j++) {
			if (j == pos)continue;
			na[i++] = tasks[j];
		}
		if (tasks != nullptr)delete[] tasks;
		tasks = na;
		size--;
	}

	Task* getTasks()const {
		return tasks;
	}

	int getSize()const {
		return size;
	}

	~Model() {
		if (tasks != nullptr)delete[] tasks;
	}
};

class View {
public:
	void showTasks(Task* tasks, int size)const {
		cout << "----------------------------------------" << endl;
		cout << "Size : " << size << endl;
		for (int i = 0; i < size; i++) {
			cout << i + 1 << ")\t" << tasks[i] << endl;
		}
	}
};

class Controller {
	Model model;
	View view;
public:
	Controller(initializer_list<Task> list) : model(list) {};

	void showTasks() {
		view.showTasks(model.getTasks(), model.getSize());
	}

	void addTask(string task, bool state) {
		model.addTask(task, state);
	}

	void deleteTask(int pos = 0) {
		model.deleteTask(pos);
	}
};

void main() {
	Task t1("Homework", false);
	Task t2("Clean the house", false);
	Task t3("Dissertation", true);
	Task t4("Buy some products", true);
	Task t5("Clean the cat litter", false);
	Controller cont({ t1, t2, t3, t4, t5});
	cont.showTasks();
	cont.addTask("Cook something for dinner", true);
	cont.showTasks();
	cont.deleteTask(2);
	cont.showTasks();
}