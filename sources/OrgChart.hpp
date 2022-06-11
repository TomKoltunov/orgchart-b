#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

const int LEVEL_ORDER = 1;
const int REVERSE_LEVEL_ORDER = 2;
const int PREORDER = 3;

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

                Node(const Node &n)
                {
                    this->_data = n._data;
                    for (Node *node : n._sons)
                    {
                        Node current = Node(*node);
                        this->_sons.push_back(&current);
                    }
                }

                Node(const Node &&n) noexcept
                {
                    this->_data = n._data;
                    this->_sons = n._sons;
                }

                Node& operator=(Node &&n) noexcept
                {
                    return *this;
                }

                Node& operator=(const Node &n) noexcept
                {
                    *this = Node(n);
                    return *this;
                }
                
                ~Node()
                {
                    for (Node *node : this->_sons)
                    {
                        node->~Node();
                    }
                }
            };

            Node *root;

        public: 

            OrgChart()
            {
                this->root = NULL;
            }

            OrgChart(OrgChart<T> &org)
            {
                if (org.root != NULL)
                {
                    this->root = new Node(org.root->_data);
                    this->root->_sons = org.root->_sons;
                }
                else // org.root == NULL 
                {
                    this->root = NULL;
                }
            }

            OrgChart(OrgChart<T> && org) noexcept
            {
                this->root = org.root;
            }

            ~OrgChart()
            {
                if (this->root == NULL)
                {
                    return;
                }
                this->root->~Node();
            }

            OrgChart& operator=(OrgChart<T> iter)
            {
                if(this != &iter)
                {
                    Node *r = this->root;
                    root = new Node(iter.root->_data);
                    delete r;
                }
                return *this;
            }
            
            OrgChart& operator=(OrgChart<T> &&iter) noexcept
            {
                if(this != &iter)
                {
                    Node *r = this->root;
                    root = new Node(iter.root->_data);
                    delete r;
                }
                return *this;
            }

            class iterator
            {
                private:
                    vector<Node*> _vec;
                    int number;

                public:
                    iterator(Node *root, int scan)
                    {
                        number = 0;
                        if (scan == LEVEL_ORDER)
                        {
                            level_order(root);
                        }
                        else if (scan == REVERSE_LEVEL_ORDER)
                        {
                            reverse_level_order(root);
                        }
                        else // scan == PREORDER
                        {
                            preorder(root);
                        }
                    }

                    bool operator==(const iterator& iter) 
                    {
                        bool answer = false;
                        if ((this->_vec.size() == 0) || (iter._vec.size() == 0))
                        {
                           answer = (this->_vec.size() == 0) && (iter._vec.size() == 0);
                        }
                        else 
                        {
                            answer = (this->_vec[(size_t)number]) == (iter._vec[(size_t)number]);
                        }
                        return answer;
                    }

                    bool operator!=(const iterator& iter)
                    {
                        bool answer = !(*this == iter);
                        return answer;
                    }

                    iterator& operator++()
                    {
                        this->number = this->number + 1;
                        if (this->number >= this->_vec.size())
                        {
                            this->_vec.clear();
                        }
                        return *this;
                    }

                    T& operator*()
                    {
                        T &answer = this->_vec[(size_t)this->number]->_data;
                        return answer;
                    }

                    T* operator->()
                    {
                        T *answer = &(this->_vec[(size_t)this->number]->_data);
                        return answer;
                    }

                    /**
                    * @brief 
                    * https://en.wikipedia.org/wiki/Breadth-first_search
                    * @param root 
                    */
                    void level_order(Node *root)
                    {
                        queue<Node*> q;
                        if (root != NULL)
                        {
                            q.push(root);
                        }
                        Node *current = NULL;
                        while (!(q.empty()))
                        {
                            for (int i = 0; i < q.size(); i++)
                            {
                                current = q.front();
                                q.pop();
                                this->_vec.push_back(current);
                                for (int j = 0; j < current->_sons.size(); j++)
                                {
                                    q.push(current->_sons[(size_t)j]);
                                }
                            }
                        }
                    }

                    /**
                    * @brief 
                    * https://en.wikipedia.org/wiki/Breadth-first_search
                    * @param root 
                    */
                    void reverse_level_order(Node *root)
                    {
                        queue<Node*> q;
                        if (root != NULL)
                        {
                            q.push(root);
                        }
                        Node *current = NULL;
                        while (!(q.empty()))
                        {
                            for (int i = 0; i < q.size(); i++)
                            {
                                current = q.front();
                                q.pop();
                                this->_vec.push_back(current);
                                for (int j = (current->_sons.size() - 1); j >= 0; j--)
                                {
                                    q.push(current->_sons[(size_t)j]);
                                }
                            }
                        }
                        vector<Node*> v;
                        for (int i = (this->_vec.size() - 1); i >= 0; i--)
                        {
                            v.push_back(this->_vec[(size_t)i]);
                        }
                        for (int i = 0; i < v.size(); i++)
                        {
                            this->_vec[(size_t)i] = v[(size_t)i];
                        }
                        this->_vec = v;
                    }

                    /**
                     * @brief 
                     * https://www.geeksforgeeks.org/iterative-preorder-traversal-of-a-n-ary-tree/
                     * @param root 
                     */
                    void preorder(Node *root)
                    {
                        stack<Node*> s;
                        if (root != NULL)
                        {
                            s.push(root);
                        }
                        while (!(s.empty()))
                        {
                            Node *temp = s.top();
                            s.pop();
                            this->_vec.push_back(temp);
                            for (int i = (temp->_sons.size() - 1); i >= 0; i--)
                            {
                                s.push(temp->_sons[(size_t)i]);
                            }
                        }
                    }
            };

            iterator begin()
            {
                if (this->root != NULL)
                {
                    return iterator(this->root, LEVEL_ORDER);
                }
                throw invalid_argument{"The tree has no root"};
            }

            iterator end()
            {
                if (this->root != NULL)
                {
                    return iterator(NULL, LEVEL_ORDER);
                }
                throw invalid_argument{"The tree has no root"};
            }

            iterator begin_level_order()
            {
                if (this->root != NULL)
                {
                    return iterator(this->root, LEVEL_ORDER);
                }
                throw invalid_argument{"The tree has no root"};
            }

            iterator end_level_order()
            {
                if (this->root != NULL)
                {
                    return iterator(NULL, LEVEL_ORDER);
                }
                throw invalid_argument{"The tree has no root"};
            }

            iterator begin_reverse_order()
            {
                if (this->root != NULL)
                {
                    return iterator(this->root, REVERSE_LEVEL_ORDER);
                }
                throw invalid_argument{"The tree has no root"};
            }

            iterator reverse_order()
            {
                if (this->root != NULL)
                {
                    return iterator(NULL, REVERSE_LEVEL_ORDER);
                }
                throw invalid_argument{"The tree has no root"};
            }

            iterator begin_preorder()
            {
                if (this->root != NULL)
                {
                    return iterator(this->root, PREORDER);
                }
                throw invalid_argument{"The tree has no root"};
            }

            iterator end_preorder()
            {
                if (this->root != NULL)
                {
                    return iterator(NULL, PREORDER);
                }
                throw invalid_argument{"The tree has no root"};
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
                    this->root = new Node(data); // this->root == NULL
                }
                return *this;
            }

            /**
             * @brief 
             * https://codereview.stackexchange.com/questions/39784/search-an-element-item-in-an-n-ary-tree
             * @param root 
             * @param data 
             * @return Node* 
             */
            Node* search(Node* root, T data)
            {
                queue<Node*> q;
                Node *found = NULL;
                Node *current = NULL;
                if (root != NULL)
                {
                    q.push(root);
                }
                bool isBreak = false;
                while (!(q.empty()))
                {
                    if (isBreak)
                    {
                        break;
                    }
                    for (int i = 0; i < q.size(); i++)
                    {
                        current = q.front();
                        q.pop();
                        for(int j = 0; j < current->_sons.size(); j++)
                        {
                            q.push(current->_sons[(size_t)j]);
                        }
                        if (current->_data == data)
                        {
                            found = current;
                            isBreak = true;
                            break;
                        }
                    }
                }
                return found;
            }

            OrgChart& add_sub(T data1, T data2)
            {
                Node *some = search(this->root, data1);
                if ((some != NULL) && (this->root != NULL) && (data1.length() != 0) && (data2.length() != 0))
                {
                    some->_sons.push_back(new Node(data2));
                    return *this;
                }
                if (data2.compare(" ") == 0 || data2.compare("\n") == 0 || data2.compare("\t") == 0 || data2.compare("\r") == 0)
                {
                    throw invalid_argument{"Sub can't be a space"};
                }
                if (data1.length() == 0)
                {
                    throw invalid_argument{"There in no node in the organization which string is equal to 'data1'"};
                }
                if (data2.length() == 0)
                {
                    throw invalid_argument{"There in no node in the organization which string is equal to 'data2'"};
                }
                if (some == NULL)
                {
                    throw invalid_argument{"There in no node in the organization which string is equal to 'data1'"};
                }
                throw invalid_argument{"The tree has no root"}; // this->root == NULL 
            }

            friend std::ostream& operator<<(std::ostream& output, OrgChart& org){

                queue<Node*>q;
            
                q.push(nullptr);
                q.pop();
                Node* root=org.root;
                if(root!=nullptr)
                {
                    q.push(root);
                }
                while(!q.empty())
                {
                    size_t len=q.size();
                    for(unsigned i=0;i<len;i++)
                    {
                        Node* n=q.front();
                        output<<n->_data<<' '; 
                        q.pop();
                        for(size_t j=0;j<n->_sons.size();j++)
                        {
                            q.push(n->_sons.at(j));
                        }
                    }
                    output<<'\n';
                }
                return output;
            }

        };
}