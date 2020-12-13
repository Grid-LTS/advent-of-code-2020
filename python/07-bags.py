import os
import re

python_dir=os.path.dirname(os.path.abspath(__file__))
input = os.path.join(os.path.dirname(python_dir),  "input/07-bags.txt")

def parse_bags1():
    bags = dict()

    def get_or_create_entry_parents(attr):
        bag = bags.get(attr, None)
        if not bag:
            bag = dict()
            bags[attr] = bag
            bag['attr'] = attr
            bag['parents'] = []
        return bag
    
    with open(input, 'r') as infile:
        for line in infile:
            parts = line.split('contain')
            result = re.match(r'(\w+ \w+) bags', parts[0].strip())
            parent_attr = result.group(1)
            parent = get_or_create_entry_parents(parent_attr)
            containments = parts[1].strip().split(', ')
            for containment in containments:
                cleaned = containment.strip("\n .")
                if cleaned == 'no other bags':
                    continue
                child_res = re.match(r'(\d+) (\w+ \w+) (\w+)', cleaned) 
                child_attr = child_res.group(2)
                child = get_or_create_entry_parents(child_attr)
                if not parent['attr'] in child['parents']:
                    child['parents'].append(parent['attr'])
        gold_bag = bags.get('shiny gold', None)
        current_bag = gold_bag
        attrs = []
        def count_parent_bags(current_bag):
            nonlocal attrs
            if not current_bag:
                return
            for parent_bag_attr in current_bag['parents']:
                parent_color = parent_bag_attr.split(' ')[1]
                if not parent_bag_attr in attrs:
                    attrs.append(parent_bag_attr)
                    count_parent_bags(bags.get(parent_bag_attr, None))
        count_parent_bags(current_bag)
        print(len(attrs))

def parse_bags2():
    bags = dict()

    def get_or_create_entry_children(attr):
        bag = bags.get(attr, None)
        if not bag:
            bag = dict()
            bags[attr] = bag
            bag['attr'] = attr
            bag['children'] = dict()
        return bag
    
    with open(input, 'r') as infile:
        for line in infile:
            parts = line.split('contain')
            result = re.match(r'(\w+ \w+) bags', parts[0].strip())
            parent_attr = result.group(1)
            parent = get_or_create_entry_children(parent_attr)
            containments = parts[1].strip().split(', ')
            for containment in containments:
                cleaned = containment.strip("\n .")
                if cleaned == 'no other bags':
                    continue
                child_res = re.match(r'(\d+) (\w+ \w+) (\w+)', cleaned) 
                child_attr = child_res.group(2)
                child = dict()
                child['attr'] = child_attr
                child['no'] = int(child_res.group(1))
                if not child_attr in parent['children'].keys():
                    parent['children'][child_attr] = child
        gold_bag = bags.get('shiny gold', None)
        current_bag = gold_bag
        children = []
        def count_children_bags(current_bag):
            nonlocal bags
            bags_no = 1
            if not current_bag:
                return 0
            if len(current_bag['children'].keys()) == 0:
                return bags_no
            for child_bag_attr in current_bag['children'].keys():
                child_bag = current_bag['children'].get(child_bag_attr)
                children.append(child_bag_attr)
                bags_no += child_bag['no'] * count_children_bags(bags.get(child_bag_attr, None))
            return bags_no 
        number = count_children_bags(current_bag) - 1
        print(number)


    
           


#parse_bags1()
parse_bags2()