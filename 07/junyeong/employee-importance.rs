struct Employee {
    id: i32,
    importance: i32,
    subordinates: Vec<i32>,
}

fn getImportance(employees: Vec<Employee>, id: i32) -> i32 {
    let mut hm = std::collections::HashMap::new();
    for employee in employees {
        hm.insert(employee.id, employee);
    }

    let mut sum = 0i32;
    if hm.len() == 0 {
        return sum;
    }

    let mut stack = vec![hm.get(&id).unwrap()];
    while stack.len() > 0 {
        let employee = stack.pop().unwrap();
        sum += employee.importance;
        for childId in &employee.subordinates {
            stack.push(hm.get(childId).unwrap());
        }
    }

    return sum;
}
