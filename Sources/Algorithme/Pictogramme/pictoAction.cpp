/*
 * =====================================================================================
 *
 *       Filename:  pictoAction.cpp
 *
 *    Description:  Tabula Rasa : Implementation de l'item Action
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:22:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "pictoAction.hpp"
#include "labelItem.hpp"
#include "pictoBuilder.hpp"
#include "algorithmeScene.hpp"
#include <QPainter>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
PictoAction::PictoAction( QString titre,
                          QString preCondition,
                          QString postCondition,
                          QGraphicsItem* parent ) :
     Pictogramme( parent ), detail_( true ), emptyDetail_( true )
{/*{{{*/
     labels_ << new LabelItem( preCondition, 150, 15, hauteurMaxAction - 10, this );
     labels_ << new LabelItem( titre, TailleMaxAction, 50, hauteurMaxAction - 10, this );
     labels_ << new LabelItem( postCondition, 150, 15, hauteurMaxAction - 10 , this );

     setAnchorType( AncreItem::Both );
     posBottomAnchor_.setY( hauteurMaxAction - 5 );
     posUpAnchor_.setY( 5 );

     updateDimension();

     addContextMenuEntry("Details", "Masquer les assertions", true);
     addContextMenuEntry("EmptyDetails", "Masquer les assertions vides", true);
}/*}}}*/

PictoAction::PictoAction(const PictoAction &item):
    Pictogramme(item),
    detail_(item.detail_), emptyDetail_(item.emptyDetail_)
{

}

/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void PictoAction::setDetailsVisible(bool visible) {
    detail_ = visible;
}

void PictoAction::setEmptyDetailsVisible(bool visible) {
    emptyDetail_ = visible;
}

void PictoAction::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{/*{{{*/
     Q_UNUSED( option );
     Q_UNUSED( widget );
     int pos = drawDetails( painter, labels_.at( 0 ), 5 );
     pos += 10;
     painter->drawRect( pos, 5,
                        labels_.at( 1 )->width(), hauteurMaxAction - 10);
     labels_.at( 1 )->setPos( pos, 5 );
     pos += labels_.at( 1 )->width() + 15;
     pos = drawDetails( painter, labels_.at( 2 ), pos );
     Pictogramme::paint( painter, option, widget );
}/*}}}*/

QRectF PictoAction::boundingRect() const
{/*{{{*/
     return QRectF( 0, 0, pos_, hauteurMaxAction );
}/*}}}*/

void PictoAction::updateDimension()
{/*{{{*/
     qreal posAncre;
     pos_ = labels_.at( 1 )->width() + 30;

     if( detail() ) {
          posAncre = ( labels_.at( 1 )->width() / 2 ) + 15;

          if( emptyDetail_ || ( !emptyDetail_ && !labels_.at( 0 )->isEmpty() ) ) {
               pos_ += labels_.at( 0 )->width() + 35;
               posAncre =  labels_.at( 0 )->width() + 50
                           + ( labels_.at( 1 )->width() / 2 );
          }

          if( emptyDetail_ || ( !emptyDetail_ && !labels_.at( 2 )->isEmpty() ) ) {
               pos_ += labels_.at( 2 )->width() + 35;
          }

     } else {
          posAncre = ( labels_.at( 1 )->width() / 2 ) + 15;
     }

     posBottomAnchor_.setX( posAncre );
     posUpAnchor_.setX( posAncre );
     updateLink();
}/*}}}*/

void PictoAction::toXml( QDomDocument& doc, QDomNode& node ) const
{/*{{{*/
     QDomElement item = doc.createElement( "Action" );
     node.appendChild( item );

     QDomElement position = doc.createElement( "Position" );
     position.appendChild( doc.createTextNode( QString( "%1;%2" ).arg( scenePos().x() )
                           .arg( scenePos().y() ) ) );
     item.appendChild( position );

     QDomElement style = doc.createElement( "StyleLien" );
     style.appendChild( doc.createTextNode(
                             ( liaison_ ) ?
                             QString::number( static_cast<int>( liaison_->style() ) ) :
                             "1" ) ) ;
     item.appendChild( style );

     QDomElement preAssertion = doc.createElement( "PreAssertion" );
     preAssertion.appendChild( doc.createTextNode( labels_.at( 0 )->label() ) );
     item.appendChild( preAssertion );

     QDomElement postAssertion = doc.createElement( "PostAssertion" );
     postAssertion.appendChild( doc.createTextNode( labels_.at( 2 )->label() ) );
     item.appendChild( postAssertion );

     QDomElement titre = doc.createElement( "Titre" );
     titre.appendChild( doc.createTextNode( labels_.at( 1 )->label() ) );
     item.appendChild( titre );

     QDomElement details = doc.createElement( "DetailsVisible" );
     details.appendChild( doc.createTextNode( detail_ ? "1" : "0" ) );
     item.appendChild( details );

     QDomElement detailsVide = doc.createElement( "DetailsVideVisible" );
     detailsVide.appendChild( doc.createTextNode( emptyDetail_ ? "1" : "0" ) );
     item.appendChild( detailsVide );

     QDomElement enfants = doc.createElement( "Enfants" );
     item.appendChild( enfants );

     AncreItem* picto;
     foreach( picto, children_ ) {
          static_cast<Pictogramme*>( picto )->toXml( doc, enfants );
     }
}/*}}}*/



/*-----------------------------------------------------------------------------
 *  Méthodes privées
 *-----------------------------------------------------------------------------*/
int PictoAction::drawDetails( QPainter* painter, LabelItem* texte, int pos ) const
{/*{{{*/
     if( detail() &&
         ( emptyDetail_ || ( !emptyDetail_ && !texte->isEmpty() ) ) ) {
          painter->drawArc( pos, 5, 10, (hauteurMaxAction / 2 ) - 5, 90 * 16, 179 * 16 );
          painter->drawArc( pos - 6, (hauteurMaxAction / 2), 15, 2, 90 * 16, 180 * 16 );
          painter->drawArc( pos, (hauteurMaxAction / 2) + 2, 10, (hauteurMaxAction / 2) - 5, 90 * 16, 179 * 16 );
          pos += 15;
          texte->setPos( pos, 4 );
          texte->setEnabled( true );
          texte->setVisible( true );
          pos += texte->width() + 5;
          painter->drawArc( pos, 5, 10, (hauteurMaxAction / 2 ) - 5, 90 * 16, -179 * 16 );
          painter->drawArc( pos + 1, (hauteurMaxAction / 2 ), 15, 2, 90 * 16, -180 * 16 );
          painter->drawArc( pos, (hauteurMaxAction / 2 ) + 2, 10, (hauteurMaxAction / 2 ) - 5, 90 * 16, -179 * 16 );
          pos += 15;

     } else {
          texte->setEnabled( false );
          texte->setVisible( false );
     }

     return pos;
}/*}}}*/

void PictoAction::createLink()
{/*{{{*/
     AncreItem::createLink();
     liaison_->setStyle( LiaisonItem::Double );
}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Gestionnaire d'évènements
 *-----------------------------------------------------------------------------*/
void PictoAction::processAction( QAction* action, QGraphicsSceneContextMenuEvent* event )
{/*{{{*/
     if( action == getContextMenuAction("Details") ) {
          detail_ = !detail_;
          prepareGeometryChange();
          updateDimension();

     } else if ( action == getContextMenuAction("EmptyDetails") ) {
          emptyDetail_ = !emptyDetail_;
          prepareGeometryChange();
          updateDimension();

     } else {
          Pictogramme::processAction( action, event );
     }
}/*}}}*/

Pictogramme *PictoAction::clone() {
    return new PictoAction(*this);
}
