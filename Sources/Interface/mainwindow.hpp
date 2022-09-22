/*
 * =====================================================================================
 *
 *       Filename:  mainwindow.hpp
 *
 *    Description:  Tabula Rasa : Classe grant l'interface de l'application
 *
 *        Version:  1.0
 *        Created:  15/08/2011 02:19:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QInputDialog>
#include "Algorithme/algorithmeScene.hpp"

class ResizeDialog;
class TabWidget;
class AboutDialog;
class LabelItem;
class QPrinter;
class QDockWidget;

namespace Ui {
class MainWindow;
}/*}}}*/


class MainWindow : public QMainWindow {
          Q_OBJECT

     public:
          MainWindow( QWidget* parent = 0 );
          ~MainWindow();

     private:
          /*-----------------------------------------------------------------------------
           *  Attributs
           *-----------------------------------------------------------------------------*/
          Ui::MainWindow* ui; // Interface
          QDockWidget* currentDock_;
          ResizeDialog* dialog; // Widget appel pour redimensionner l'algorithme
          AboutDialog* about_; // Widget lors de la demande de l'A-propos
          QList<Pictogramme*> copyBuffer_;

          /*-----------------------------------------------------------------------------
           * Methodes prives
           *-----------------------------------------------------------------------------*/
          void selectQAction( AlgorithmeScene::Mode mode );
          void setDisabled( bool state );
          TabWidget* createNewTab(Algorithm* algorithm);
          void removeCurrentDictionaryDock();
          void showDictionaryDock(QDockWidget* dockToShow);
          TabWidget* getTabWidgetAt(int index);
          virtual void closeEvent( QCloseEvent* event );

     private slots:
          /*-----------------------------------------------------------------------------
           *  Slots des actions de la barre de gauche
           *-----------------------------------------------------------------------------*/
          void selectedTabChanged(int);
          void on_actionMode_Edition_triggered( bool checked );
          void on_actionMode_Insertion_triggered( bool checked );
          void on_actionAction_triggered( bool checked );
          void on_actionIteration_triggered( bool checked );
          void on_actionProcedure_triggered( bool checked );
          void on_actionCondition_triggered( bool checked );
          void on_actionConditionMultiple_triggered( bool checked );
          void on_actionSortie_triggered( bool checked );

          /*-----------------------------------------------------------------------------
           *  Slot de l'interface
           *-----------------------------------------------------------------------------*/
          void on_tabWidget_tabCloseRequested( int index );
          void on_actionNouveau_triggered();
          void on_actionExporter_vers_une_image_triggered();
          void on_actionRenommer_l_algorithme_triggered();
          void on_actionFermer_l_onglet_triggered();
          void on_actionRedimensionner_l_Algorithme_triggered();
          void on_actionA_propos_de_Tabula_Rasa_triggered();
          void on_actionImprimer_triggered();
          void on_actionEnregistrer_triggered( int index = -1 );
          void on_actionOuvrir_triggered();


          /*-----------------------------------------------------------------------------
           * Slots divers
           *-----------------------------------------------------------------------------*/
          void resizeScene( int width, int height ); //redimensionne la scne
          void setMode( AlgorithmeScene::Mode mode ); //Change le mode
          void print( QPrinter* device ); // Imprime l'algorithme
          void itemAdded( Pictogramme* item ); //Pour connecter un labelItem ou slot changeLabel
          void changeLabel( LabelItem* item ); //Appel pour changer l'intitul d'un LabelItem
          void liaisonError();
          void on_actionTout_s_lectionner_triggered();
          void on_actionExporter_SVG_triggered();
          void on_actionExporter_en_PDF_triggered();
          void on_actionSauvegarder_sous_triggered();
          void on_actionQuitter_triggered();
          void on_actionSupprimer_la_s_lection_triggered();
          void on_actionCopier_la_s_lection_triggered();
          void on_actionColler_la_s_lection_triggered();
};
#endif                           // MAINWINDOW_HPP
