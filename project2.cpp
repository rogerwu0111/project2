#include <iostream>

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
    {StackArray = new block*[StackSize];}

    void Push(block* Blocks){StackArray[currentSize] = Blocks; currentSize++;}

    block* Top(){return this->StackArray[currentSize-1];}

    void Pop(){this->StackArray[currentSize-1] = NULL; currentSize--;}
};

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
    {Set_of_blocks = new block*[Size_of_set];}

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

            else
            {
                arr[i][j].setDistance(0);

                arr[i][j].setPredecessor(&arr[i][j]);
            }
        }
    }
}

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

//******checking function******//

void print_dis_pre(int row, int col, block** arr)
{
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            cout << arr[i][j].getDistance() << " ";
        }

        cout << endl;
    }
}

//******end of checking******//

int main()
{
    int rows, columns;

    cin >> rows;

    cin >> columns;

    char** input = new char*[rows];

    for (int i=0; i<rows; i++)
    {
        input[i] = new char[columns];
    }

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
        {
            cin >> input[i][j];
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

    print_dis_pre(rows, columns, dis_pre);

    return 0;
}