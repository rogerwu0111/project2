#include <iostream>
#include <fstream>
using namespace std;

#define MaxDistance 999999999

// used to store the information of distance and predecessor
class block
{
private:
    int Distance;
    block* Predecessor;
    int rows;
    int cols;
public:

    ~block(){}

    block(int dis=-1, block* pre=NULL, int rows=-1, int cols=-1)
    :Distance(dis), Predecessor(pre), rows(rows), cols(cols){}

    void setDistance(int dis){this->Distance = dis;}

    void setPredecessor(block* pre){this->Predecessor = pre;}

    void setRows(int rows){this->rows = rows;}

    void setCols(int cols){this->cols = cols;}

    int getDistance(){return this->Distance;}

    block* getPredecessor(){return this->Predecessor;}

    int getRows(){return this->rows;}

    int getCols(){return this->cols;}
};

class Stack
{
private:
    block** StackArray;
    int StackSize;
    int currentSize;
public:

    ~Stack(){delete []StackArray;}

    Stack(int Size=10):StackSize(Size), currentSize(0)
    {StackArray = new block*[Size];}

    void Push(block* Blocks){this->StackArray[currentSize] = Blocks; currentSize++;}

    block* Top(){return this->StackArray[currentSize-1];}

    void Pop(){this->StackArray[currentSize-1] = NULL; currentSize--;}
};

class Queue
{
private:
    block** QueueArray;
    int QueueSize;
    int Front;
    int Rear;
public:

    ~Queue(){delete []QueueArray;}

    Queue(int Size=100):QueueSize(Size), Front(0), Rear(0)
    {QueueArray = new block*[Size];}

    void Push(block* Blocks);

    block* Top(){return this->QueueArray[Front];}

    void Pop(){this->QueueArray[Front] = NULL; Front++;}


};

void::Queue::Push(block* Blocks)
{
    if (Rear >= QueueSize)
    {
        QueueSize += 100;

        block** newQueue = new block*[QueueSize];

        for (int i=Front; i<Rear; i++) newQueue[i] = QueueArray[i];

        delete []QueueArray;

        QueueArray = newQueue;
    }

    QueueArray[Rear] = Blocks;

    Rear++;
}

// is used in Dijkstra
class BlockSet
{
private:
    block** Set_of_blocks;
    int Size_of_set;
    int currentSize;
public:

    ~BlockSet(){delete []Set_of_blocks;}

    BlockSet(int Size=10):Size_of_set(Size), currentSize(0)
    {Set_of_blocks = new block*[Size];}

    block* ExtractMin();

    void addBlocks(block* Blocks){Set_of_blocks[currentSize] = Blocks; currentSize++;}

    void Initialize_BlockSet(int row, int col, block** arr);

    int getCurrentSize(){return this->currentSize;}
};

block*::BlockSet::ExtractMin()
{
    block* MinBlock = Set_of_blocks[0];

    int Min = 0;

    for (int i=1; i<currentSize; i++)
    {
        if (Set_of_blocks[i]->getDistance() < MinBlock->getDistance())
        {
            MinBlock = Set_of_blocks[i];

            Min = i;
        }
    }

    Set_of_blocks[Min] = Set_of_blocks[currentSize-1];

    Set_of_blocks[currentSize-1] = NULL;

    currentSize--;

    return MinBlock;
}

// used in Dijkstra algorithm
void::BlockSet::Initialize_BlockSet(int row, int col, block** arr)
{
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            if (arr[i][j].getDistance() == MaxDistance)
            {
                addBlocks(&arr[i][j]);
            }
        }
    }
}

// used to initialize dis_pre. all walls have distance = -1
void Initialize_BlockArray(int row, int col, block** arr, char** input)
{
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            arr[i][j].setRows(i);

            arr[i][j].setCols(j);

            if (input[i][j] == '0') arr[i][j].setDistance(MaxDistance);

            else if (input[i][j] == '1');

            else arr[i][j].setDistance(0);
        }
    }
}

// return number of blocks need to clean initially. not include 'R'
int Number_of_Blocks(int row, int col, char** input)
{
    int number = 0;

    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            if (input[i][j] == '0') number++;
        }
    }

    return number;
}

// find charging position
void starting_point(int row, int col, char** input, int* r, int* c)
{
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            if (input[i][j] == 'R')
            {
                *r = i;

                *c = j;
            }
        }
    }
}

// Dijkstra algorithm
void BlockArray(int row, int col, block** arr, char** input, int startRow, int startColumn)
{
    int BlocksNum = Number_of_Blocks(row, col, input);

    BlockSet Set(BlocksNum);

    Set.Initialize_BlockSet(row, col, arr);

    int currentRow = startRow;

    int currentCol = startColumn;

    while(Set.getCurrentSize() != 0)
    {
        int currentlength = arr[currentRow][currentCol].getDistance();

        block* currentblock = &arr[currentRow][currentCol];

        if (currentRow+1 < row)
        {
            if (arr[currentRow+1][currentCol].getDistance() != -1
                && arr[currentRow+1][currentCol].getDistance() > currentlength+1)
            {
                arr[currentRow+1][currentCol].setDistance(currentlength+1);

                arr[currentRow+1][currentCol].setPredecessor(currentblock);
            }
        }

        if (currentRow-1 >= 0)
        {
            if (arr[currentRow-1][currentCol].getDistance() != -1
                && arr[currentRow-1][currentCol].getDistance() > currentlength+1)
            {
                arr[currentRow-1][currentCol].setDistance(currentlength+1);

                arr[currentRow-1][currentCol].setPredecessor(currentblock);
            }
        }

        if (currentCol+1 < col)
        {
            if (arr[currentRow][currentCol+1].getDistance() != -1
                && arr[currentRow][currentCol+1].getDistance() > currentlength+1)
            {
                arr[currentRow][currentCol+1].setDistance(currentlength+1);

                arr[currentRow][currentCol+1].setPredecessor(currentblock);
            }
        }

        if (currentCol-1 >= 0)
        {
            if (arr[currentRow][currentCol-1].getDistance() != -1
                && arr[currentRow][currentCol-1].getDistance() > currentlength+1)
            {
                arr[currentRow][currentCol-1].setDistance(currentlength+1);

                arr[currentRow][currentCol-1].setPredecessor(currentblock);
            }
        }

        block* temp = Set.ExtractMin();

        currentRow = temp->getRows();

        currentCol = temp->getCols();
    }

    Set.~BlockSet();
}

// return the step of going to farthest point
int Go_To_Farthest(int row, int col, block** arr, bool** IfCleaned,
                   Queue& q, int& BlocksLeft, block* &current_position)
{
    int MaxSteps = 0;

    block* MaxBlock = NULL;

    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            if (IfCleaned[i][j] == 0)
            {
                if (arr[i][j].getDistance() > MaxSteps)
                {
                    MaxSteps = arr[i][j].getDistance();

                    MaxBlock = &arr[i][j];
                }
            }
        }
    }

    if (MaxBlock) current_position = MaxBlock;

    Stack S(MaxSteps+1);

    S.Push(MaxBlock);

    block* current = S.Top();

    for (int i=1; i<=MaxSteps-1; i++)
    {
        current = current->getPredecessor();

        S.Push(current);
    }

    for (int i=1; i<=MaxSteps; i++)
    {
        current = S.Top();

        if (IfCleaned[current->getRows()][current->getCols()] == 0)
        {
            IfCleaned[current->getRows()][current->getCols()] = 1;

            BlocksLeft--;
        }

        q.Push(current);

        S.Pop();
    }

    S.~Stack();

    return MaxSteps;
}

int Go_To_Nearest(int row, int col, block** arr, bool** IfCleaned,
                  Queue& q, int& BlocksLeft, block* &current_position)
{
    int MinSteps = MaxDistance;

    block* MinBlock = NULL;

    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            if (IfCleaned[i][j] == 0)
            {
                if (arr[i][j].getDistance() < MinSteps && arr[i][j].getDistance() > 0)
                {
                    MinSteps = arr[i][j].getDistance();

                    MinBlock = &arr[i][j];
                }
            }
        }
    }

    if (MinBlock) current_position = MinBlock;

    else MinSteps = 0;

    Stack S(MinSteps+1);

    S.Push(MinBlock);

    block* current = S.Top();

    for (int i=1; i<=MinSteps-1; i++)
    {
        current = current->getPredecessor();

        S.Push(current);
    }

    for (int i=1; i<=MinSteps; i++)
    {
        current = S.Top();

        if (IfCleaned[current->getRows()][current->getCols()] == 0)
        {
            IfCleaned[current->getRows()][current->getCols()] = 1;

            BlocksLeft--;
        }

        q.Push(current);

        S.Pop();
    }

    S.~Stack();

    return MinSteps;
}

bool IsValid(int row, int col, int batteryLeft, block** arr,
             bool** IfCleaned, int testRow, int testCol)
{
    if (testRow > row-1 || testCol > col-1 || testRow < 0 || testCol < 0) return 0;

    else
    {
        int stepsNeeded = arr[testRow][testCol].getDistance();

        if (stepsNeeded == 0) return 0;

        else if (IfCleaned[testRow][testCol] == 0 && batteryLeft >= stepsNeeded) return 1;

        else return 0;
    }
}

bool IfCountinue(int row, int col, int batteryLeft, block** arr,
                 bool** IfCleaned, int testRow, int testCol)
{
    if (IsValid(row, col, batteryLeft, arr, IfCleaned, testRow+1, testCol) ||
        IsValid(row, col, batteryLeft, arr, IfCleaned, testRow-1, testCol) ||
        IsValid(row, col, batteryLeft, arr, IfCleaned, testRow, testCol+1) ||
        IsValid(row, col, batteryLeft, arr, IfCleaned, testRow, testCol-1)) return 1;

    else return 0;
}

void Walk_Near_By(int row, int col, int& batteryLeft, block** arr, int& total_steps,
                bool** IfCleaned, Queue& q, int &BlocksLeft, block* &current_position)
{
    int currentRow = current_position->getRows();

    int currentCol = current_position->getCols();

    while (current_position->getDistance() != 0 &&
           IfCountinue(row, col, batteryLeft, arr, IfCleaned, currentRow, currentCol))
    {
        int MinDis = MaxDistance;

        int nextRow = -1;

        int nextCol = -1;

        if (IsValid(row, col, batteryLeft-1, arr, IfCleaned, currentRow+1, currentCol))
        {
            if (MinDis > arr[currentRow+1][currentCol].getDistance())
            {
                MinDis = arr[currentRow+1][currentCol].getDistance();

                nextRow = currentRow+1;

                nextCol = currentCol;
            }
        }

        if (IsValid(row, col, batteryLeft-1, arr, IfCleaned, currentRow-1, currentCol))
        {
            if (MinDis > arr[currentRow-1][currentCol].getDistance())
            {
                MinDis = arr[currentRow-1][currentCol].getDistance();

                nextRow = currentRow-1;

                nextCol = currentCol;
            }
        }

        if (IsValid(row, col, batteryLeft-1, arr, IfCleaned, currentRow, currentCol+1))
        {
            if (MinDis > arr[currentRow][currentCol+1].getDistance())
            {
                MinDis = arr[currentRow][currentCol+1].getDistance();

                nextRow = currentRow;

                nextCol = currentCol+1;
            }
        }

        if (IsValid(row, col, batteryLeft-1, arr, IfCleaned, currentRow, currentCol-1))
        {
            if (MinDis > arr[currentRow][currentCol-1].getDistance())
            {
                MinDis = arr[currentRow][currentCol-1].getDistance();

                nextRow = currentRow;

                nextCol = currentCol-1;
            }
        }

        currentRow = nextRow;

        currentCol = nextCol;

        current_position = &arr[nextRow][nextCol];

        IfCleaned[nextRow][nextCol] = 1;

        q.Push(&arr[nextRow][nextCol]);

        total_steps++;

        batteryLeft--;

        BlocksLeft--;
    }
}

int Go_Back(int row, int col, block** arr, bool** IfCleaned,
            Queue& q, int& BlocksLeft, block* &current_position)
{
    block* current = current_position;

    int currentRow = current->getRows();

    int currentCol = current->getCols();

    int dis = current->getDistance();

    for (int i=0; i<dis; i++)
    {
        current_position = current_position->getPredecessor();

        current = current->getPredecessor();

        currentRow = current->getRows();

        currentCol = current->getCols();

        if (IfCleaned[currentRow][currentCol] == 0)
        {
            IfCleaned[currentRow][currentCol] = 1;

            BlocksLeft--;
        }

        q.Push(current);
    }

    return dis;
}

void cleaning_floor(int row, int col, int battery, block** arr,
                    int startRow, int startCol, ofstream& OutputFile)
{
    bool** IfCleaned = new bool*[row];

    int BlocksLeft = 0;

    for (int i=0; i<row; i++)
    {
        IfCleaned[i] = new bool[col];
    }

    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            if (arr[i][j].getDistance() >= 0)
            {
                IfCleaned[i][j] = 0;

                BlocksLeft++;
            }

            else IfCleaned[i][j] = 1;
        }
    }

    int total_steps = 0;

    int batteryLeft = battery;

    block* current_position = &arr[startRow][startCol];

    Queue q;

    q.Push(&arr[startRow][startCol]);

    while(BlocksLeft)
    {
        int steps = 0;

        steps = Go_To_Nearest(row, col, arr, IfCleaned, q, BlocksLeft, current_position);

        batteryLeft -= steps;

        total_steps += steps;

        Walk_Near_By(row, col, batteryLeft, arr, total_steps, IfCleaned, q, BlocksLeft, current_position);

        if (current_position == &arr[startRow][startCol])
        {
            batteryLeft = battery;
        }

        else
        {
            steps = Go_Back(row, col, arr, IfCleaned, q, BlocksLeft, current_position);

            batteryLeft = battery;

            total_steps += steps;
        }
    }

    OutputFile << total_steps << endl;

    for (int i=0; i<total_steps+1; i++)
    {
        OutputFile << q.Top()->getRows() << " " << q.Top()->getCols() << endl;

        q.Pop();
    }
}
//******checking function******//

void print_dis_pre(int row, int col, block** arr, ofstream& OutputFile)
{
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            OutputFile << arr[i][j].getDistance() << " ";
        }

        OutputFile << endl;
    }
}

void go_single_path(int row, int col, block** arr, int& BlocksLeft,
                    int startRow, int startCol, ofstream& OutputFile)
{
    bool** IfCleaned = new bool*[row];

    for (int i=0; i<row; i++)
    {
        IfCleaned[i] = new bool[col];
    }

    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            if (arr[i][j].getDistance() >= 0)
            {
                IfCleaned[i][j] = 0;

                BlocksLeft++;
            }

            else IfCleaned[i][j] = 1;
        }
    }

    Queue q;

    int steps = 0;

    block* current_position = &arr[startRow][startCol];

    int batteryLeft = 100;

    //steps = Go_To_Farthest(row, col, arr, IfCleaned, q, BlocksLeft, current_position);
    steps = Go_To_Nearest(row, col, arr, IfCleaned, q, BlocksLeft, current_position);

    Walk_Near_By(row, col, batteryLeft, arr, steps, IfCleaned, q, BlocksLeft, current_position);

    OutputFile << steps << endl;

    block* current = NULL;

    for (int i=1; i<=steps; i++)
    {
        current = q.Top();

        OutputFile << current->getRows() << " " << current->getCols() << endl;

        q.Pop();
    }
}

//******end of checking******//

int main()
{
    ifstream InputFile;

    ofstream OutputFile;

    InputFile.open("floor.data");

    OutputFile.open("final.path");

    int rows, columns, Battery;

    InputFile >> rows;

    InputFile >> columns;

    InputFile >> Battery;

    char** input = new char*[rows];

    for (int i=0; i<rows; i++)
    {
        input[i] = new char[columns];
    }

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
        {
            InputFile >> input[i][j];
        }
    }

    block** dis_pre = new block* [rows];

    for (int i=0; i<rows; i++)
    {
        dis_pre[i] = new block[columns];
    }

    Initialize_BlockArray(rows, columns, dis_pre, input);

    int startRow, startColumn;

    starting_point(rows, columns, input, &startRow, &startColumn);

    BlockArray(rows, columns, dis_pre, input, startRow, startColumn);

    //print_dis_pre(rows, columns, dis_pre, OutputFile);

    //int test = 1000;

    //go_single_path(rows, columns, dis_pre, test, startRow, startColumn, OutputFile);

    cleaning_floor(rows, columns, Battery, dis_pre, startRow, startColumn, OutputFile);

    return 0;
}