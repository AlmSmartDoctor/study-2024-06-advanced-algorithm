/**
 * Definition for Employee.
 * class Employee {
 *     id: number
 *     importance: number
 *     subordinates: number[]
 *     constructor(id: number, importance: number, subordinates: number[]) {
 *         this.id = (id === undefined) ? 0 : id;
 *         this.importance = (importance === undefined) ? 0 : importance;
 *         this.subordinates = (subordinates === undefined) ? [] : subordinates;
 *     }
 * }
 */

function getImportance(employees: Employee[], id: number): number {
  const employeeMap = new Map<number, Employee>();
  for (const employee of employees) {
    employeeMap.set(employee.id, employee);
  }

  function dfs(empId: number): number {
    const employee = employeeMap.get(empId);
    if (!employee) return 0;

    let totalImportance = employee.importance;

    for (const subId of employee.subordinates) {
      totalImportance += dfs(subId);
    }

    return totalImportance;
  }

  return dfs(id);
}
