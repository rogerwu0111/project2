#include <iostream>

using namespace std;


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

    void Push(block* Blocks){StackArray[currentSize] = Blocks;}

    block* Top(){return this->StackArray[currentSize-1];}
};

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

void Initialize_BlockArray(int row, int col, block**arr, char** input)
{
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            arr[i][j].setRows(i);

            arr[i][j].setCols(j);

            if (input[i][j] == '0') arr[i][j].setDistance(999999999);

            else if (input[i][j] == '1');

            else
            {
                arr[i][j].setDistance(0);

                arr[i][j].setPredecessor(&arr[i][j]);
            }
        }
    }
}

void BlockArray(int row, int col, block**arr, char** input)
{

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



    return 0;
}