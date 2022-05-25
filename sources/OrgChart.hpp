#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

#define LEVEL_ORDER 1
#define REVERSE_LEVEL_ORDER 2
#define PREORDER 3

namespace ariel
{

    template <class T = string>

    class OrgChart
    {
        private:
            struct Node{
                T _data;
                vector<Node*> _sons;
                Node(T &data) : _data(data) 
                {
                    
                } 
            };

            Node *root;

        public: 
            class iterator
            {
                private:
                    vector<Node*> _vec;
                    int number;

                public:
                    iterator(Node *root, int scan)
                    {
                        this->number = 0;
                        if (scan == LEVEL_ORDER)
                        {
                            level_order(root);
                        }
                        else if (scan == REVERSE_LEVEL_ORDER)
                        {
                            reverse_level_order(root);
                        }
                        else 
                        {
                            preorder(root);
                        }
                    }

                    bool operator==(const iterator& iter) 
                    {
                        bool answer;
                        if ((this->_vec.size() == 0) || (iter._vec.size() == 0))
                        {
                           answer = (this->_vec.size() == 0) && (iter._vec.size() == 0);
                        }
                        else 
                        {
                            answer = (this->_vec[number]) == (iter._vec[number]);
                        }
                        return answer;
                    }

                    bool operator!=(const iterator& iter)
                    {
                        bool answer = !(*this == iter);
                        return false;
                    }

                    iterator& operator++()
                    {
                        if (number >= this->_vec.size())
                        {
                            this->_vec.clear();
                        }
                        this->number = this->number + 1;
                        return *this;
                    }

                    string& operator*()
                    {
                        string answer = this->_vec[this->number]->_data;
                        return answer;
                    }

                    string* operator->()
                    {
                        string *answer = &(this->_vec[this->number]->_data);
                        return answer;
                    }

                    void level_order(Node *root)
                    {

                    }

                    void reverse_level_order(Node *root)
                    {

                    }

                    void preorder(Node *root)
                    {

                    }
            };

            iterator begin()
            {
                if (this->root != NULL)
                {
                    return iterator(this->root, LEVEL_ORDER);
                }
                else // this->root == NULL
                {
                    throw invalid_argument{"The tree has no root"};
                }
            }

            iterator end()
            {
                if (this->root != NULL)
                {
                    return iterator(NULL, LEVEL_ORDER);
                }
                else // this->root == NULL
                {
                    throw invalid_argument{"The tree has no root"};
                }
            }

            iterator begin_level_order()
            {
                if (this->root != NULL)
                {
                    return iterator(this->root, LEVEL_ORDER);
                }
                else // this->root == NULL
                {
                    throw invalid_argument{"The tree has no root"};
                }
            }

            iterator end_level_order()
            {
                if (this->root != NULL)
                {
                    return iterator(NULL, LEVEL_ORDER);
                }
                else // this->root == NULL
                {
                    throw invalid_argument{"The tree has no root"};
                }
            }

            iterator begin_reverse_order()
            {
                if (this->root != NULL)
                {
                    return iterator(this->root, REVERSE_LEVEL_ORDER);
                }
                else // this->root == NULL
                {
                    throw invalid_argument{"The tree has no root"};
                }
            }

            iterator reverse_order()
            {
                if (this->root != NULL)
                {
                    return iterator(NULL, REVERSE_LEVEL_ORDER);
                }
                else // this->root == NULL
                {
                    throw invalid_argument{"The tree has no root"};
                }
            }

            iterator begin_preorder()
            {
                if (this->root != NULL)
                {
                    return iterator(this->root, PREORDER);
                }
                else // this->root == NULL
                {
                    throw invalid_argument{"The tree has no root"};
                }
            }

            iterator end_preorder()
            {
                if (this->root != NULL)
                {
                    return iterator(NULL, PREORDER);
                }
                else // this->root == NULL
                {
                    throw invalid_argument{"The tree has no root"};
                }
            }

            OrgChart& add_root(T data)
            {
                if ((this->root != NULL) && (data.length() != 0))
                {
                    this->root->_data = data;
                }
                else // (this->root == NULL) || (data.length() == 0)
                {
                    if (data.length() == 0)
                    {
                        throw invalid_argument{"There is no node which string is equal to'data'"};
                    }
                    else // this->root == NULL
                    {
                        this->root = new Node(data);
                    }
                }
                return *this;
            }

            OrgChart& add_sub(T data1, T data2)
            {
                return *this;
            }

            friend ostream& operator<<(ostream& output, const OrgChart &organization)
            {
                return output;
            }
    };
}