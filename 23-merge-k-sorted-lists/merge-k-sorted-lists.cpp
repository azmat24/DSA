class Solution {
public:

    struct Compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {

        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;


        for (ListNode* node : lists) {
            if (node != NULL) {
                pq.push(node);
            }
        }


        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;

        while (!pq.empty()) {

           
            ListNode* node = pq.top();
            pq.pop();

            current->next = node;
            current = current->next;

            if (node->next != NULL) {
                pq.push(node->next);
            }
        }

        return dummy->next;
    }
};