#include "ClassifyData.h"

ClassifyData::ClassifyData(DefaultIO* io, ClientDetails* clientDetails)
{
    this->setDescription("3. classify data\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
    
}

void ClassifyData::execute()
{
    if (this->getClientDetails()->getClassified().empty() 
    || this->getClientDetails()->getUnclassified().empty()) {
        this->getIO()->write("please upload data\n");
        return;
    }

    Knn *knn = new Knn(this->getClientDetails()->getK(), &this->getClientDetails()->getClassified(),
                        this->getClientDetails()->getAlgorithm());
    int size = this->getClientDetails()->getUnclassified().size();

    // run on the vectors and classify each
    for (int i = 0; i < size; ++i) {
        this->getClientDetails()->getUnclassified()[i].first = knn->findVectorType(this->getClientDetails()->getUnclassified()[i].second);
    }
    this->getIO()->write("classifying data complete\n");
}