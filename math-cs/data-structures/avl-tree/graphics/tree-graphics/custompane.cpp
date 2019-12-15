#include <iostream>

#include "custompane.h"
using namespace std;

CustomPane::CustomPane(QWidget *parent) : QWidget(parent) {
    temp_tree = NULL;
}

void CustomPane::paintEvent(QPaintEvent *event) {
    paint = new QPainter(this);
    QPen linePen(Qt::blue);
    linePen.setWidth(3);
    paint->setPen(linePen);
    if (temp_tree != NULL) {
        qDebug("Tree not null");
        pathRenderRec(temp_tree->getRoot());
    }
    else {
        qDebug("Tree NULL");
    }
}

/*
void CustomPane::pathRender() {
    pathRenderRec(temp_tree->getRoot());
    update();
    cout << "ok" << endl;
}
*/
void CustomPane::pathRenderRec(Node<int> *node) {
    if (node != NULL) {
        cout << "KEY RENDER: " << node->getKey() << " left x: " <<  node->line_left->dx() <<
             " y: " << node->line_left->dx() << " | right x: " << node->line_right->dx() <<
             " y: " << node->line_right->dy() << endl;
        //qDebug("KEY RENDER: " + to_string(node->getKey()));
        paint->drawLine(*node->line_left);
        paint->drawLine(*node->line_right);
        pathRenderRec(node->getLeft());
        pathRenderRec(node->getRight());
    }
}

void CustomPane::paintPane(Tree<int> *tree) {
    temp_tree = tree;
    update();
}
