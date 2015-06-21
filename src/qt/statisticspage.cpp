#include "statisticspage.h"
#include "ui_statisticspage.h"
#include "main.h"
#include "wallet.h"
#include "init.h"
#include "base58.h"
#include "clientmodel.h"
#include "bitcoinrpc.h"
#include <sstream>
#include <string>

using namespace json_spirit;


StatisticsPage::StatisticsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsPage)
{
    ui->setupUi(this);
    setFixedSize(400, 420);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerCountDown()));
    timer->start(1000);


}

int heightPrevious = -1;
int connectionPrevious = -1;
int volumePrevious = -1;
double rewardPrevious = -1;
double netPawratePrevious = -1;
double pawratePrevious = -1;
double hardnessPrevious = -1;
double hardnessPrevious2 = -1;
int stakeminPrevious = -1;
int stakemaxPrevious = -1;
QString stakecPrevious = "";
int inc1 = 10;


void StatisticsPage::updateStatistics()
{
    double pHardness = GetDifficulty();
    double pHardness2 = GetDifficulty(GetLastBlockIndex(pindexBest, true));
    int pPawrate = GetPoWMHashPS();
    double pPawrate2 = 0.000;
    int nHeight = pindexBest->nHeight;
    double nSubsidy = nHeight;
    uint64_t nMinWeight = 0, nMaxWeight = 0, nWeight = 0;
    pwalletMain->GetStakeWeight(*pwalletMain, nMinWeight, nMaxWeight, nWeight);
    uint64_t nNetworkWeight = GetPoSKernelPS();
    int64_t volume = ((pindexBest->nMoneySupply)/100000000);
    int peers = this->model->getNumConnections();
    pPawrate2 = (double)pPawrate;
    QString height = QString::number(nHeight);
    QString stakemin = QString::number(nMinWeight);
    QString stakemax = QString::number(nNetworkWeight);
    QString phase = "";
    QString LastPoWBlock = QString::number(LAST_POW_BLOCK);

    ui->labelPhasePoW->setText("PoW = Block 0 - " + LastPoWBlock);
    ui->labelPhasePoS->setText("PoS = Block 16000 - onwards");


    if (pindexBest->nHeight < LAST_POW_BLOCK)
    {
        phase = "Proof of Work";
        if (pindexBest->nHeight < 1)
    {
        nSubsidy = 40000000 * COIN; // 40000000 ICO
    }
    else if (pindexBest->nHeight < 101)
    {
        nSubsidy = 0 * COIN; // fair launch
    } 
    else if (pindexBest->nHeight < 1101)
    {
        nSubsidy = 500 * COIN; // 500000
    }     
    else if (pindexBest->nHeight < 2101){
        nSubsidy = 600 * COIN; // 600000  
    }   
    else if (pindexBest->nHeight < 3101){
        nSubsidy = 700 * COIN; // 700000  
    }   
    else if (pindexBest->nHeight < 4101){
        nSubsidy = 800 * COIN; // 800000  
    }   
    else if (pindexBest->nHeight < 5101){
        nSubsidy = 900 * COIN; // 900000  
    }   
    else if (pindexBest->nHeight < 6101){
        nSubsidy = 1000 * COIN; // 1000000 
    }   
    else if (pindexBest->nHeight < 7101){
        nSubsidy = 1100 * COIN; // 1100000  
    }   
    else if (pindexBest->nHeight < 8101){
        nSubsidy = 1200 * COIN; // 1200000  
    }   
    else if (pindexBest->nHeight < 9101){
        nSubsidy = 1300 * COIN; // 1300000  
    }   
    else if (pindexBest->nHeight < 10101){
        nSubsidy = 1400 * COIN; // 1400000  
    }   
    else if (pindexBest->nHeight < 11101){
        nSubsidy = 1500 * COIN; // 1500000  
    }   
    else if (pindexBest->nHeight < 12101){
        nSubsidy = 1600 * COIN; // 1600000 
    }   
    else if (pindexBest->nHeight < 13101){
        nSubsidy = 1700 * COIN; // 1700000  
    }   
    else if (pindexBest->nHeight < 14101){
        nSubsidy = 1800 * COIN; // 1800000  
    }   
    else if (pindexBest->nHeight < 15101){
        nSubsidy = 1900 * COIN; // 1900000  
    }   
    else if (pindexBest->nHeight < 16101){
        nSubsidy = 2000 * COIN; // 2000000  
    }   
    ;
    }
    else
    {
        phase = "Proof of Stake";
        nSubsidy = 0 ;
    }

    QString subsidy = QString::number(nSubsidy, 'f', 6);
    QString hardness = QString::number(pHardness, 'f', 6);
    QString hardness2 = QString::number(pHardness2, 'f', 6);
    QString pawrate = QString::number(pPawrate2, 'f', 3);
    QString Qlpawrate = model->getLastBlockDate().toString();

    QString QPeers = QString::number(peers);
    QString qVolume = QString::number(volume);

    if(nHeight > heightPrevious)
    {
        ui->heightBox->setText("<b><font color=\"green\">" + height + "</font></b>");
    } else {
    ui->heightBox->setText(height);
    }

    if(0 > stakeminPrevious)
    {
        ui->minBox->setText("<b><font color=\"green\">" + stakemin + "</font></b>");
    } else {
    ui->minBox->setText(stakemin);
    }
    if(0 > stakemaxPrevious)
    {
        ui->maxBox->setText("<b><font color=\"green\">" + stakemax + "</font></b>");
    } else {
    ui->maxBox->setText(stakemax);
    }

    if(phase != stakecPrevious)
    {
        ui->cBox->setText("<b><font color=\"green\">" + phase + "</font></b>");
    } else {
    ui->cBox->setText(phase);
    }

    
    if(nSubsidy < rewardPrevious)
    {
        ui->rewardBox->setText("<b><font color=\"red\">" + subsidy + "</font></b>");
    } else {
    ui->rewardBox->setText(subsidy);
    }
    
    if(pHardness > hardnessPrevious)
    {
        ui->diffBox->setText("<b><font color=\"orange\">" + hardness + "</font></b>");        
    } else if(pHardness < hardnessPrevious) {
        ui->diffBox->setText("<b><font color=\"red\">" + hardness + "</font></b>");
    } else {
        ui->diffBox->setText(hardness);        
    }

    if(pHardness2 > hardnessPrevious2)
    {
        ui->diffBox2->setText("<b><font color=\"orange\">" + hardness2 + "</font></b>");
    } else if(pHardness2 < hardnessPrevious2) {
        ui->diffBox2->setText("<b><font color=\"red\">" + hardness2 + "</font></b>");
    } else {
        ui->diffBox2->setText(hardness2);
    }
    
    if(pPawrate2 > netPawratePrevious)
    {
        ui->pawrateBox->setText("<b><font color=\"orange\">" + pawrate + " MH/s</font></b>");
    } else if(pPawrate2 < netPawratePrevious) {
        ui->pawrateBox->setText("<b><font color=\"red\">" + pawrate + " MH/s</font></b>");
    } else {
        ui->pawrateBox->setText(pawrate + " MH/s");
    }

    if(Qlpawrate != pawratePrevious)
    {
        ui->localBox->setText("<b><font color=\"orange\">" + Qlpawrate + "</font></b>");
    } else {
    ui->localBox->setText(Qlpawrate);
    }
    
    if(peers > connectionPrevious)
    {
        ui->connectionBox->setText("<b><font color=\"orange\">" + QPeers + "</font></b>");             
    } else if(peers < connectionPrevious) {
        ui->connectionBox->setText("<b><font color=\"red\">" + QPeers + "</font></b>");        
    } else {
        ui->connectionBox->setText(QPeers);  
    }

    if(volume > volumePrevious)
    {
        ui->volumeBox->setText("<b><font color=\"orange\">" + qVolume + " SMSR" + "</font></b>");
    } else if(volume < volumePrevious) {
        ui->volumeBox->setText("<b><font color=\"red\">" + qVolume + " SMSR" + "</font></b>");
    } else {
        ui->volumeBox->setText(qVolume + " SMSR");
    }
    updatePrevious(nHeight, nMinWeight, nNetworkWeight, phase, nSubsidy, pHardness, pHardness2, pPawrate2, Qlpawrate, peers, volume);
}

void StatisticsPage::updatePrevious(int nHeight, int nMinWeight, int nNetworkWeight, QString phase, double nSubsidy, double pHardness, double pHardness2, double pPawrate2, QString Qlpawrate, int peers, int volume)
{
    heightPrevious = nHeight;
    stakeminPrevious = nMinWeight;
    stakemaxPrevious = nNetworkWeight;
    stakecPrevious = phase;
    rewardPrevious = nSubsidy;
    hardnessPrevious = pHardness;
    hardnessPrevious2 = pHardness2;
    netPawratePrevious = pPawrate2;
    pawratePrevious = Qlpawrate;
    connectionPrevious = peers;
    volumePrevious = volume;
}

void StatisticsPage::setModel(ClientModel *model)
{
    updateStatistics();
    this->model = model;

}


StatisticsPage::~StatisticsPage()
{
    delete ui;
}

void StatisticsPage::timerCountDown()
{
    inc1 = inc1 - 1;
    ui->labelCountDown->setText(QString::number(inc1) + "s");
    if (inc1 == 0)
    {
        updateStatistics();
        inc1 = 10;
    }
}


