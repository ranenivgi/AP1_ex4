#include "ClassifyData.h"

/**
 * @brief Construct a new Classify Data:: Classify Data object
 *
 * @param io
 * @param clientDetails
 */
ClassifyData::ClassifyData(DefaultIO *io, ClientDetails *clientDetails)
{
    this->setDescription("3. classify data\n");
    this->setIO(io);
    this->setClientDetails(clientDetails);
}

/**
 * @brief executes the classify command which classifies the data inserted in the upload command
 *
 */
void ClassifyData::execute()
{
    // checks if the user uploaded data
    if (this->getClientDetails()->getClassified().empty() || this->getClientDetails()->getUnclassified().empty())
    {
        this->getIO()->write("please upload data\n");
        return;
    }

    int size = this->getClientDetails()->getUnclassified().size();
    // classify each vector using the KNN algorithm
    for (int i = 0; i < size; ++i)
    {
        Knn *knn = new Knn(this->getClientDetails()->getK(), this->getClientDetails()->getUnclassified()[i].second,
                           &this->getClientDetails()->getClassified(), this->getClientDetails()->getAlgorithm());
        this->getClientDetails()->getUnclassified()[i].first = knn->findVectorType();
    }
    this->getIO()->write("classifying data complete\n");
}