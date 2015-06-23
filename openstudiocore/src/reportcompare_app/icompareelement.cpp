#include "icompareelement.h"
#include <idoc.h>

ICompareElement::ICompareElement(IDoc *doc)
    :doc(doc)
{
    reset();
}

ICompareElement::~ICompareElement()
{

}

QString ICompareElement::getError()
{
    return errMsg;
}

void ICompareElement::clearError()
{
    errMsg.clear();
}

const QString &ICompareElement::projectName()
{
    return doc->projectName();
}
