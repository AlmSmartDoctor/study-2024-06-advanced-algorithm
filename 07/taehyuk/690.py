"""
# Definition for Employee.
class Employee:
    def __init__(self, id: int, importance: int, subordinates: List[int]):
        self.id = id
        self.importance = importance
        self.subordinates = subordinates
"""

class Solution:
    def getImportance(self, employees: List['Employee'], id: int) -> int:
        employeeDic = {employee.id: employee for employee in employees}

        def DFS(id):
            importance = employeeDic[id].importance            
            for subordinateId in employeeDic[id].subordinates:
                importance += DFS(subordinateId)
            return importance
        
        return DFS(id)
        