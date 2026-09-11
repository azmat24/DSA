class Solution {
public:

    struct Compare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {

        priority_queue<ListNode*, vector<ListNode*>, Compare> pq;

        // Har list ka first node heap mein daalo
        for (ListNode* node : lists) {
            if (node != NULL) {
                pq.push(node);
            }
        }

        // Dummy node
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;

        while (!pq.empty()) {

            // Sabse chhoti value wala node
            ListNode* node = pq.top();
            pq.pop();

            // Answer mein add
            current->next = node;
            current = current->next;

            // Next node heap mein daalo
            if (node->next != NULL) {
                pq.push(node->next);
            }
        }

        return dummy->next;
    }
};