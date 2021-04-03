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
    y = m.addVars(40, vtype=GRB.BINARY, name="y")
    

    # Set objective
    m.setObjective(ltot, GRB.MINIMIZE)


    # Add constraint
    
    #total number of layers
    m.addGenConstrMax(ltot, [l1, l2, l3, l4, l5, l6, l7, l8, \
                             l9, l10, l11, l12, l13, l14, l15, \
                             l16, l17, l18, l19, l20, l21, l22], name="maxconstr")
    #m.addConstr(ltot == max(l1, l2, l3, l4, l5, l6, l7, l8, \
    #l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, \
    #l19, l20, l21, l22), "total_num_layer") -> this does not work

    #proximity conflict:
    m.addConstr((y[0] == 1) >> (l1 + 1 <= l13))
    m.addConstr((y[1] == 1) >> (l13 + 1 <= l1))
    m.addConstr(y[0] + y[1] == 1)
    m.addConstr((y[2] == 1) >> (l1 + 1 <= l14))
    m.addConstr((y[3] == 1) >> (l14 + 1 <= l1))
    m.addConstr(y[2] + y[3] == 1)
    m.addConstr((y[4] == 1) >> (l1 + 1 <= l15))
    m.addConstr((y[5] == 1) >> (l15 + 1 <= l1))
    m.addConstr(y[4] + y[5] == 1)
    m.addConstr((y[6] == 1) >> (l1 + 1 <= l16))
    m.addConstr((y[7] == 1) >> (l16 + 1 <= l1))
    m.addConstr(y[6] + y[7] == 1)
    m.addConstr((y[8] == 1) >> (l1 + 1 <= l17))
    m.addConstr((y[9] == 1) >> (l17 + 1 <= l1))
    m.addConstr(y[8] + y[9] == 1)
    m.addConstr((y[10] == 1) >> (l1 + 1 <= l18))
    m.addConstr((y[11] == 1) >> (l18 + 1 <= l1))
    m.addConstr(y[10] + y[11] == 1)
    m.addConstr((y[12] == 1) >> (l1 + 1 <= l19))
    m.addConstr((y[13] == 1) >> (l19 + 1 <= l1))
    m.addConstr(y[12] + y[13] == 1)
    m.addConstr((y[14] == 1) >> (l1 + 1 <= l20))
    m.addConstr((y[15] == 1) >> (l20 + 1 <= l1))
    m.addConstr(y[14] + y[15] == 1)
    m.addConstr((y[16] == 1) >> (l1 + 1 <= l21))
    m.addConstr((y[17] == 1) >> (l21 + 1 <= l1))
    m.addConstr(y[16] + y[17] == 1)
    m.addConstr((y[18] == 1) >> (l1 + 1 <= l22))
    m.addConstr((y[19] == 1) >> (l22 + 1 <= l1))
    m.addConstr(y[18] + y[19] == 1)
    m.addConstr((y[20] == 1) >> (l2 + 1 <= l12))
    m.addConstr((y[21] == 1) >> (l12 + 1 <= l2))
    m.addConstr(y[20] + y[21] == 1)
    m.addConstr((y[22] == 1) >> (l3 + 1 <= l12))
    m.addConstr((y[23] == 1) >> (l12 + 1 <= l3))
    m.addConstr(y[22] + y[23] == 1)
    m.addConstr((y[24] == 1) >> (l4 + 1 <= l12))
    m.addConstr((y[25] == 1) >> (l12 + 1 <= l4))
    m.addConstr(y[24] + y[25] == 1)
    m.addConstr((y[26] == 1) >> (l5 + 1 <= l12))
    m.addConstr((y[27] == 1) >> (l12 + 1 <= l5))
    m.addConstr(y[26] + y[27] == 1)
    m.addConstr((y[28] == 1) >> (l6 + 1 <= l12))
    m.addConstr((y[29] == 1) >> (l12 + 1 <= l6))
    m.addConstr(y[28] + y[29] == 1)
    m.addConstr((y[30] == 1) >> (l7 + 1 <= l12))
    m.addConstr((y[31] == 1) >> (l7 + 1 <= l12))
    m.addConstr(y[30] + y[31] == 1)
    m.addConstr((y[32] == 1) >> (l8 + 1 <= l12))
    m.addConstr((y[33] == 1) >> (l12 + 1 <= l8))
    m.addConstr(y[32] + y[33] == 1)
    m.addConstr((y[34] == 1) >> (l9 + 1 <= l12))
    m.addConstr((y[35] == 1) >> (l12 + 1 <= l9))
    m.addConstr(y[34] + y[35] == 1)
    m.addConstr((y[36] == 1) >> (l10 + 1 <= l12))
    m.addConstr((y[37] == 1) >> (l12 + 1 <= l10))
    m.addConstr(y[36] + y[37] == 1)
    m.addConstr((y[38] == 1) >> (l11 + 1 <= l12))
    m.addConstr((y[39] == 1) >> (l12 + 1 <= l11))
    m.addConstr(y[38] + y[39] == 1)

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