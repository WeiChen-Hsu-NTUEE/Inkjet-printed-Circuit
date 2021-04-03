import gurobipy as gp
from gurobipy import GRB

try:

    # Create a new model
    m = gp.Model("mip1")

    # Create variables
    l1 = m.addVar(vtype=GRB.INTEGER, name="l1")
    l2 = m.addVar(vtype=GRB.INTEGER, name="l2")
    l3 = m.addVar(vtype=GRB.INTEGER, name="l3")
    l4 = m.addVar(vtype=GRB.INTEGER, name="l4")
    l5 = m.addVar(vtype=GRB.INTEGER, name="l5")
    l6 = m.addVar(vtype=GRB.INTEGER, name="l6")
    l7 = m.addVar(vtype=GRB.INTEGER, name="l7")
    l8 = m.addVar(vtype=GRB.INTEGER, name="l8")
    l9 = m.addVar(vtype=GRB.INTEGER, name="l9")
    l10 = m.addVar(vtype=GRB.INTEGER, name="l10")
    l11 = m.addVar(vtype=GRB.INTEGER, name="l11")
    l12 = m.addVar(vtype=GRB.INTEGER, name="l12")
    l13 = m.addVar(vtype=GRB.INTEGER, name="l13")
    l14 = m.addVar(vtype=GRB.INTEGER, name="l14")
    l15 = m.addVar(vtype=GRB.INTEGER, name="l15")
    l16 = m.addVar(vtype=GRB.INTEGER, name="l16")
    l17 = m.addVar(vtype=GRB.INTEGER, name="l17")
    l18 = m.addVar(vtype=GRB.INTEGER, name="l18")
    l19 = m.addVar(vtype=GRB.INTEGER, name="l19")
    l20 = m.addVar(vtype=GRB.INTEGER, name="l20")
    l21 = m.addVar(vtype=GRB.INTEGER, name="l21")
    l22 = m.addVar(vtype=GRB.INTEGER, name="l22")
    ltot = m.addVar(vtype=GRB.INTEGER, name="ltot")

    # Set objective
    m.setObjective(ltot, GRB.MINIMIZE)

    # Add constraint

    #total number of the layers:
    m.addConstr(ltot == max(l1, l2, l3, l4, l5, l6, l7, l8, \
    l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, \
    l19, l20, l21, l22), "total_num_layer")

    #proximity conflict:
    m.addConstr(l1 != l13, "proximity1")
    m.addConstr(l1 != l14, "proximity2")
    m.addConstr(l1 != l15, "proximity3")
    m.addConstr(l1 != l16, "proximity4")
    m.addConstr(l1 != l17, "proximity5")
    m.addConstr(l1 != l18, "proximity6")
    m.addConstr(l1 != l19, "proximity7")
    m.addConstr(l1 != l20, "proximity8")
    m.addConstr(l1 != l21, "proximity9")
    m.addConstr(l1 != l22, "proximity10")
    m.addConstr(l2 != l12, "proximity11")
    m.addConstr(l3 != l12, "proximity12")
    m.addConstr(l4 != l12, "proximity13")
    m.addConstr(l5 != l12, "proximity14")
    m.addConstr(l6 != l12, "proximity15")
    m.addConstr(l7 != l12, "proximity16")
    m.addConstr(l8 != l12, "proximity17")
    m.addConstr(l9 != l12, "proximity18")
    m.addConstr(l10 != l12, "proximity19")
    m.addConstr(l11 != l12, "proximity20")

    #laplace conflict:
    m.addConstr(l2 + 1 <= l1, "laplace1")
    m.addConstr(l2 + 1 <= l13, "laplace2")
    m.addConstr(l3 + 1 <= l1, "laplace3")
    m.addConstr(l3 + 1 <= l13, "laplace4")
    m.addConstr(l3 + 1 <= l14, "laplace5")
    m.addConstr(l4 + 1 <= l1, "laplace6")
    m.addConstr(l5 + 1 <= l1, "laplace7")
    m.addConstr(l5 + 1 <= l16, "laplace8")
    m.addConstr(l6 + 1 <= l1, "laplace9")
    m.addConstr(l6 + 1 <= l16, "laplace10")
    m.addConstr(l7 + 1 <= l1, "laplace11")
    m.addConstr(l8 + 1 <= l1, "laplace12")
    m.addConstr(l9 + 1 <= l1, "laplace13")
    m.addConstr(l9 + 1 <= l19, "laplace14")
    m.addConstr(l10 + 1 <= l1, "laplace15")
    m.addConstr(l11 + 1 <= l1, "laplace16")
    m.addConstr(l11 + 1 <= l21, "laplace17")
    m.addConstr(l11 + 1 <= l22, "laplace18")
    m.addConstr(l13 + 1 <= l12, "laplace19")
    m.addConstr(l14 + 1 <= l12, "laplace20")
    m.addConstr(l14 + 1 <= l4, "laplace21")
    m.addConstr(l15 + 1 <= l12, "laplace22")
    m.addConstr(l15 + 1 <= l4, "laplace23")
    m.addConstr(l15 + 1 <= l5, "laplace24")
    m.addConstr(l16 + 1 <= l12, "laplace25")
    m.addConstr(l17 + 1 <= l12, "laplace26")
    m.addConstr(l17 + 1 <= l6, "laplace27")
    m.addConstr(l17 + 1 <= l7, "laplace28")
    m.addConstr(l18 + 1 <= l12, "laplace29")
    m.addConstr(l18 + 1 <= l7, "laplace30")
    m.addConstr(l18 + 1 <= l8, "laplace31")
    m.addConstr(l19 + 1 <= l12, "laplace32")
    m.addConstr(l19 + 1 <= l8, "laplace33")
    m.addConstr(l20 + 1 <= l12, "laplace34")
    m.addConstr(l20 + 1 <= l9, "laplace35")
    m.addConstr(l20 + 1 <= l10, "laplace36")
    m.addConstr(l21 + 1 <= l12, "laplace37")
    m.addConstr(l21 + 1 <= l10, "laplace38")
    m.addConstr(l22 + 1 <= l12, "laplace39")

    # Optimize model
    m.optimize()

    for v in m.getVars():
        print('%s %g' % (v.varName, v.x))

    print('Obj: %g' % m.objVal)

except gp.GurobiError as e:
    print('Error code ' + str(e.errno) + ': ' + str(e))

except AttributeError:
    print('Encountered an attribute error')